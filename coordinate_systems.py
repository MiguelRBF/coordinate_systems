# --- CORDINATE SYSTEMS ---
#--------------------------------------------
# Module name:      coordinate_systems.py
# Created by:       rbf
#--------------------------------------------
'''
This module was created to manage the change between coordinate systems
'''

#### IMPORT STANDARD LIBRARIES ####
from math import pi

####  ####

#### IMPORT DOWNLOADED LIBRARIES ####
import numpy as np

####  ####

#### IMPORT MODULES ####

####  ####

#### VARIABLE DEFINITION ####

## --- World Geodetic System webs ---
# Web0: http://wiki.gis.com/wiki/index.php/Geodetic_system
# Web1: https://en.wikipedia.org/wiki/Geodetic_datum
# ---  ---

# --- WGS84 Elipsoidal model: World Geodetic System 1984 ---
# Web2: http://www.jpz.se/Html_filer/wgs_84.html
# Web3: https://en.wikipedia.org/wiki/Latitude#Ellipsoidal-harmonic_coordinates

# Semi-major axis [m]
a_wgs84 = 6378137.0

# Flattening
f_wgs84 = 1/298.257223563

# Semi-minor axis (1-f)*a [m]
b_wgs84 = a_wgs84*(1-f_wgs84)

# First eccentricity squared e1**2 = 1 – (b/a)**2 = (2–f)*f (¿yellow mark VSC?)
e12_wgs84 = (2.0 - f_wgs84)*f_wgs84

# Second eccentricity squared e2**2 = (a/b)**2-1 = f*(2-f)/(1-f)**2
e22_wgs84 = f_wgs84*(2-f_wgs84)/(1-f_wgs84)**2

# ---  ---

####  ####

#### FUNCTIONS DEFINITION ####

def llh2ecef(lat: np.float64, long: np.float64, h: np.float64):
    '''
    Convert lat, long, height in WGS84 to ECEF X,Y,Z.
    Longitude and latitude must be given in decimal degrees.
     Altitude must be given in meters.

    np arrays can be given as inputs.

    Equations taken from Web0.
    '''

    # Convert longitude-latitude units from degrees to radians
    lat = lat*pi/180
    long = long*pi/180

    # Compute chi parameter
    chi = np.sqrt(1-e12_wgs84*(np.sin(lat))**2)

    # Comput x, y and z coordinates
    x = (a_wgs84/chi +h)*np.cos(lat)*np.cos(long)
    y = (a_wgs84/chi +h)*np.cos(lat)*np.sin(long)
    z = (a_wgs84*(1-e12_wgs84)/chi + h)*np.sin(lat)

    return x, y, z

def ecef2enu_ecefRef(refX: np.float64, refY: np.float64, refZ: np.float64, x: np.float64, y: np.float64, z: np.float64):
    '''This function convert ECEF coordinates to local east, north, up coordinates (ENU).

    A reference point in ECEF coordinates (x, y, z - refX, refY, refZ)
    must be given. All distances are in metres.

    np arrays can be given as inputs.

    Equations taken from Web0.
    '''

    # First find reference location in latitude, longitud and height coordinates
    refLat, refLong, refH = ecef2llh(refX, refY, refZ)

    # Convert the latitude and longitude into radians
    refLat = refLat*pi/180
    refLong = refLong*pi/180

    # Compute ENU coordinates
    e = -np.sin(refLong)*(x-refX) + np.cos(refLong)*(y-refY)
    n = -np.sin(refLat)*np.cos(refLong)*(x-refX) - np.sin(refLat)*np.sin(refLong)*(y-refY) + np.cos(refLat)*(z-refZ)
    u = np.cos(refLat)*np.cos(refLong)*(x-refX) + np.cos(refLat)*np.sin(refLong)*(y-refY) + np.sin(refLat)*(z-refZ)

    return e, n, u

def ecef2enu_llhRef(refLat: np.float64, refLong: np.float64, refH: np.float64, x: np.float64, y: np.float64, z: np.float64):
    '''This function convert ECEF coordinates to local east, north, up coordinates.

    A reference point in geodetic coordinate system 
    (latitude, longitude, height - refLat, refLong, refH)
    must be given. All distances are in metres.
    
    np arrays can be given as inputs.

    Equations taken from Web0.
    '''

    # First find reference location in ECEF coordinates
    refX, refY, refZ = llh2ecef(refLat, refLong, refH)

    # Compute ENU coordinates
    e = -np.sin(refLong)*(x-refX) + np.cos(refLong)*(y-refY)
    n = -np.sin(refLat)*np.cos(refLong)*(x-refX) - np.sin(refLat)*np.sin(refLong)*(y-refY) + np.cos(refLat)*(z-refZ)
    u = np.cos(refLat)*np.cos(refLong)*(x-refX) + np.cos(refLat)*np.sin(refLong)*(y-refY) + np.sin(refLat)*(z-refZ)

    return e, n, u

def enu2ecef_ecefRef(refX: np.float64, refY: np.float64, refZ: np.float64, e: np.float64, n: np.float64, u: np.float64):
    '''This function convert local east, north, up coordinates (labeled e, n, u) to ECEF coordinates.

    A reference point in ECEF coordinates (x, y, z - refX, refY, refZ)
    must be given. All distances are in metres.

    np arrays can be given as inputs.

    Equations taken from Web0.
    '''

    # First find reference location in ECEF coordinates
    refLat, refLong, refH = ecef2llh(refX, refY, refZ)

    # Convert the latitude and longitude into radians
    refLat = refLat*pi/180
    refLong = refLong*pi/180

    # Compute ecef coordinates
    x = -np.sin(refLong)*e - np.cos(refLong)*np.sin(refLat)*n + np.cos(refLong)*np.cos(refLat)*u + refX
    y = np.cos(refLong)*e - np.sin(refLong)*np.sin(refLat)*n + np.cos(refLat)*np.sin(refLong)*u + refY
    z = np.cos(refLat)*n + np.sin(refLat)*u + refZ

    return x, y, z

def enu2ecef_llhRef(refLat: np.float64, refLong: np.float64, refH: np.float64, e: np.float64, n: np.float64, u: np.float64):
    '''This function convert local east, north, up coordinates (labeled e, n, u) to ECEF coordinates.

    A reference point in geodetic coordinate system
    (latitude, longitude, height - refLat, refLong, refH)
    must be given. All distances are in metres.

    np arrays can be given as inputs.

    Equations taken from Web0.
    '''

    # First find reference location in ECEF coordinates
    refX, refY, refZ = llh2ecef(refLat, refLong, refH)

    # Compute ecef coordinates
    x = -np.sin(refLong)*e - np.cos(refLong)*np.sin(refLat)*n + np.cos(refLong)*np.cos(refLat)*u + refX
    y = np.cos(refLong)*e - np.sin(refLong)*np.sin(refLat)*n + np.cos(refLat)*np.sin(refLong)*u + refY
    z = np.cos(refLat)*n + np.sin(refLat)*u + refZ

    return x, y, z

def ecef2llh(x: np.float64, y: np.float64, z: np.float64):
    '''This function was created to change between ECEF coordinate system to 
    geodetic coordinate system (longitude, latitude, height).

    np arrays can be given as inputs.

    Equations taken from Web0.
    '''

    r2 = x**2+y**2
    r = np.sqrt(r2)
    E2 = a_wgs84**2 - b_wgs84**2
    F = 54*b_wgs84**2*z**2
    G = r2 + (1-e12_wgs84)*z**2 - e12_wgs84*E2
    c = (e12_wgs84*e12_wgs84*F*r2)/(G*G*G)
    s = ( 1 + c + np.sqrt(c*c + 2*c) )**(1/3)
    P = F/(3*(s+1/s+1)**2*G*G)
    Q = np.sqrt(1+2*e12_wgs84*e12_wgs84*P)
    ro = -(e12_wgs84*P*r)/(1+Q) + np.sqrt((a_wgs84*a_wgs84/2)*(1+1./Q) - ((1-e12_wgs84)*P*z**2)/(Q*(1+Q)) - P*r2/2)
    tmp = (r - e12_wgs84*ro)**2
    U = np.sqrt( tmp + z**2 )
    V = np.sqrt( tmp + (1-e12_wgs84)*z**2 )
    zo = (b_wgs84**2*z)/(a_wgs84*V)

    # Now get the final coordinates: longitude, latitude and altitude
    lat = np.arctan((z+e22_wgs84*zo)/r)
    long = np.arctan2(y, x)
    h = U*(1 - b_wgs84**2/(a_wgs84*V))

    # Convert the units of longitude and latitude from radians to degrees
    lat = lat*180/pi
    long = long*180/pi

    return lat, long, h

####  ####

#### MAIN FUNCTION DEFINITION ####
def main():

    ## FUNCTIONS USAGE EXAMPLE ##

    # Set the precission of the terminal printing of np arrays
    np.set_printoptions(precision=20)

    # Bern and Sydney coordinates (WGS84: latitude, longitude, height)
    array_lat = np.array([46.9480900, -33.8678500])
    array_long = np.array([7.4474400, 151.2073200])
    array_h = np.array([549, 58])

    print(f'Bern and Sydney coordinates (latitude, longitude, height)')
    print(f'array_lat:  {array_lat}')
    print(f'array_long: {array_long}')
    print(f'array_h:    {array_h}')
    print()

    # Get the cordinates in ecef reference system
    array_x, array_y, array_z = llh2ecef(array_lat, array_long, array_h)

    print(f'Get the cordinates in ecef reference system')
    print(f'array_x:    {array_x}')
    print(f'array_y:    {array_y}')
    print(f'array_z:    {array_z}')
    print()

    # Get the cordinates into geodetic reference system (WGS84: latitude, longitude, height)
    array2_lat, array2_long, array2_h = ecef2llh(array_x, array_y, array_z)

    print(f'Get the cordinates into geodetic reference system (WGS84: latitude, longitude, height)')
    print(f'array2_lat: {array2_lat}')
    print(f'array2_long:{array2_long}')
    print(f'array2_h:   {array2_h}')
    print()

    # Supose a reference GNSS station in Bern with and ENU error of:
    # E=1.0m , N=0.798654m and U=1.6543m
    # Use as reference the Bern position
    #
    # Supose a reference GNSS station in Sydney with and ENU error of:
    # E=0.1m , N=0.0798654m and U=0.16543m
    # Use as reference the Sydney position
    array_E = np.array([1.0, 0.1])
    array_N = np.array([0.798654, 0.0798654])
    array_U = np.array([1.6543, 0.16543])

    print(f'Bern and Sydney ENU error in GNSS reference station [m]')
    print(f'array_E:    {array_E}')
    print(f'array_N:    {array_N}')
    print(f'array_U:    {array_U}')
    print()

    print(f'Using Bern and Sydney ecef position as reference...')
    print()

    array2_x, array2_y, array2_z = enu2ecef_ecefRef(array_x, array_y, array_z, array_E, array_N, array_U)

    print(f'Get the cordinates in ecef from ENU reference system.')
    print(f'array2_x:    {array2_x}')
    print(f'array2_y:    {array2_y}')
    print(f'array2_z:    {array2_z}')
    print()

    array2_E, array2_N, array2_U = ecef2enu_ecefRef(array_x, array_y, array_z, array2_x, array2_y, array2_z)

    print(f'Get the cordinates in ENU from ecef reference system.')
    print(f'array2_E:    {array2_E}')
    print(f'array2_N:    {array2_N}')
    print(f'array2_U:    {array2_U}')
    print()

    print(f'Using Bern and Sydney llh position as reference...')
    print()

    array3_x, array3_y, array3_z = enu2ecef_llhRef(array_lat, array_long, array_h, array_E, array_N, array_U)

    print(f'Get the cordinates in ecef from ENU reference system.')
    print(f'array3_x:    {array3_x}')
    print(f'array3_y:    {array3_y}')
    print(f'array3_z:    {array3_z}')
    print()

    array3_E, array3_N, array3_U = ecef2enu_llhRef(array_lat, array_long, array_h, array3_x, array3_y, array3_z)

    print(f'Get the cordinates in ENU from ecef reference system.')
    print(f'array3_E:    {array3_E}')
    print(f'array3_N:    {array3_N}')
    print(f'array3_U:    {array3_U}')
    print()

    ##  ##

####  ####

if __name__=="__main__":

    main()