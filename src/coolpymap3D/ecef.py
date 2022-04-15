# --- Origin ECEF coordinate system ---
#--------------------------------------------
# Module name:      ecef.py
# Created by:       MiguelRBF
#--------------------------------------------
'''
This module was created to transforms from ECEF 
(earth-centered, earth-fixed) frame to others.
'''

#### IMPORT STANDARD LIBRARIES ####
from math import pi

####  ####

#### IMPORT DOWNLOADED LIBRARIES ####
import numpy as np

####  ####

#### IMPORT MODULES ####
from .ellipsoid import Ellipsoid
from .lla import lla2ecef

####  ####

#### VARIABLE DEFINITION ####

# The __all__ tells the semantically “public” names from the module.
# If there is a name in __all__, the users are expected to use it, 
# and they can expect that it will not change.
# https://appdividend.com/2021/05/09/what-is-python-__all__-and-how-to-use-it/
__all__ = [
    "ecef2llh",
    "ecef2enu_ecefRef",
    "ecef2enu_llaRef"
]

####  ####

#### FUNCTIONS DEFINITION ####

def ecef2llh(
    x: np.float64,
    y: np.float64,
    z: np.float64,
    ell: Ellipsoid = None,
    deg: bool = True
    ):
    '''This function was created to change between ECEF coordinate system to 
    geodetic of specified ellipsoid (default WGS-84) coordinate system 
    (longitude, latitude, height).

    np arrays can be given as inputs.

    Equations taken from:
    http://wiki.gis.com/wiki/index.php/Geodetic_system

    Parameters
    ----------
    x
        target x ECEF coordinate (meters)
    y
        target y ECEF coordinate (meters)
    z
        target z ECEF coordinate (meters)
    
    ell : Ellipsoid, optional
          reference ellipsoid
    deg : bool, optional
          degrees input/output  (False: radians in/out)

    Returns
    -------
    lat
        target geodetic latitude
    lon
        target geodetic longitude
    alt
        target altitude above geodetic ellipsoid (meters)
    '''
    # If no ellipsoid is defined define the default ellipsoid (WGS84)
    if ell is None:
        ell = Ellipsoid()

    r2 = x**2+y**2
    r = np.sqrt(r2)
    E2 = ell.a**2 - ell.b**2
    F = 54*ell.b**2*z**2
    G = r2 + (1-ell.e2)*z**2 - ell.e2*E2
    c = (ell.e2*ell.e2*F*r2)/(G*G*G)
    s = ( 1 + c + np.sqrt(c*c + 2*c) )**(1/3)
    P = F/(3*(s+1/s+1)**2*G*G)
    Q = np.sqrt(1+2*ell.e2*ell.e2*P)
    ro = -(ell.e2*P*r)/(1+Q) + np.sqrt((ell.a*ell.a/2)*(1+1./Q) - ((1-ell.e2)*P*z**2)/(Q*(1+Q)) - P*r2/2)
    tmp = (r - ell.e2*ro)**2
    U = np.sqrt( tmp + z**2 )
    V = np.sqrt( tmp + (1-ell.e2)*z**2 )
    zo = (ell.b**2*z)/(ell.a*V)

    # Now get the final coordinates: longitude, latitude and altitude
    lat = np.arctan((z+ell.ep2*zo)/r)
    long = np.arctan2(y, x)
    alt = U*(1 - ell.b**2/(ell.a*V))

    # If degres is wanted as output
    if deg:
        # Convert the units of longitude and latitude from radians to degrees
        lat = lat*180/pi
        long = long*180/pi

    return lat, long, alt

def ecef2enu_ecefRef(
    refX: np.float64,
    refY: np.float64,
    refZ: np.float64,
    x: np.float64,
    y: np.float64,
    z: np.float64,
    ):
    '''This function convert ECEF coordinates to local east, north, up coordinates (ENU).

    A reference point in ECEF coordinates (x, y, z - refX, refY, refZ)
    must be given. All distances are in metres.

    np arrays can be given as inputs.

    Equations taken from:
    http://wiki.gis.com/wiki/index.php/Geodetic_system

    Parameters
    ----------
    refX
        reference x ECEF coordinate (meters)
    refY
        reference y ECEF coordinate (meters)
    refZ
        reference z ECEF coordinate (meters)
    x
        target x ECEF coordinate (meters)
    y
        target y ECEF coordinate (meters)
    z
        target z ECEF coordinate (meters)

    Returns
    -------
    e
        target east ENU coordinate (meters)
    n
        target north ENU coordinate (meters)
    u
        target up ENU coordinate (meters)
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

def ecef2enu_llaRef(
    refLat: np.float64,
    refLong: np.float64,
    refAlt: np.float64,
    x: np.float64,
    y: np.float64,
    z: np.float64,
    ell: Ellipsoid = None,
    deg: bool = True
    ):
    '''This function convert ECEF coordinates to local east, north, up coordinates.

    A reference point in geodetic coordinate system 
    (latitude, longitude, height - refLat, refLong, refH)
    must be given. All distances are in metres.
    
    np arrays can be given as inputs.

    Equations taken from:
    http://wiki.gis.com/wiki/index.php/Geodetic_system

    Parameters
    ----------
    
    refLat
        reference geodetic latitude
    refLong
        reference geodetic longitude
    refAlt
        reference altitude above geodetic ellipsoid (meters)
    x
        target x ECEF coordinate (meters)
    y
        target y ECEF coordinate (meters)
    z
        target z ECEF coordinate (meters)
    
    ell : Ellipsoid, optional
          reference ellipsoid
    deg : bool, optional
          degrees input/output  (False: radians in/out)

    Returns
    -------
    e
        target east ENU coordinate (meters)
    n
        target north ENU coordinate (meters)
    u
        target up ENU coordinate (meters)
    '''
    # If no ellipsoid is defined define the default ellipsoid (WGS84)
    if ell is None:
        ell = Ellipsoid()

    # First find reference location in ECEF coordinates
    refX, refY, refZ = lla2ecef(refLat, refLong, refAlt, ell, deg)

    # Compute ENU coordinates
    e = -np.sin(refLong)*(x-refX) + np.cos(refLong)*(y-refY)
    n = -np.sin(refLat)*np.cos(refLong)*(x-refX) - np.sin(refLat)*np.sin(refLong)*(y-refY) + np.cos(refLat)*(z-refZ)
    u = np.cos(refLat)*np.cos(refLong)*(x-refX) + np.cos(refLat)*np.sin(refLong)*(y-refY) + np.sin(refLat)*(z-refZ)

    return e, n, u

####  ####

# End of document: ecef.py