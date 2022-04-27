# --- CORDINATE SYSTEMS ---
#--------------------------------------------
# Module name:      coordinate_systems_PY_example.py
# Created by:       MiguelRBF
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
from src.coolPyMap3D.ellipsoid import Ellipsoid
from src.coolPyMap3D.ecef import ecef2lla, ecef2enu_ecefRef, ecef2enu_llaRef
from src.coolPyMap3D.lla import lla2ecef
from src.coolPyMap3D.enu import enu2ecef_ecefRef, enu2ecef_llaRef

####  ####

#### VARIABLE DEFINITION ####

####  ####

#### MAIN FUNCTION DEFINITION ####
def main():

    # Define the ellipsoid to be use (WGS84)
    ellipsoid_wgs84 = Ellipsoid('wgs84')

    ## FUNCTIONS USAGE EXAMPLE ##

    # Set the precission of the terminal printing of np arrays
    np.set_printoptions(precision=20)

    # Bern and Sydney coordinates (WGS84: latitude, longitude, altitude)
    array_lat = np.array([46.9480900, -33.8678500])
    array_long = np.array([7.4474400, 151.2073200])
    array_a = np.array([549, 58])

    print(f'Bern and Sydney coordinates (latitude, longitude, altitude)')
    print(f'array_lat:  {array_lat}')
    print(f'array_long: {array_long}')
    print(f'array_a:    {array_a}')
    print()

    # Get the cordinates in ecef reference system
    array_x, array_y, array_z = lla2ecef(array_lat, array_long, array_a, ell=ellipsoid_wgs84, deg=True)

    print(f'Get the cordinates in ecef reference system')
    print(f'array_x:    {array_x}')
    print(f'array_y:    {array_y}')
    print(f'array_z:    {array_z}')
    print()

    # Get the cordinates into geodetic reference system (WGS84: latitude, longitude, height)
    array2_lat, array2_long, array2_h = ecef2lla(array_x, array_y, array_z, ell=ellipsoid_wgs84, deg=True)

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

    array2_E, array2_N, array2_U = ecef2enu_ecefRef(array_x, array_y, array_z, array2_x, array2_y, array2_z, ell=ellipsoid_wgs84)

    print(f'Get the cordinates in ENU from ecef reference system.')
    print(f'array2_E:    {array2_E}')
    print(f'array2_N:    {array2_N}')
    print(f'array2_U:    {array2_U}')
    print()

    print(f'Using Bern and Sydney lla position as reference...')
    print()

    array3_x, array3_y, array3_z = enu2ecef_llaRef(array_lat, array_long, array_a, array_E, array_N, array_U, ell=ellipsoid_wgs84, deg=True)

    print(f'Get the cordinates in ecef from ENU reference system.')
    print(f'array3_x:    {array3_x}')
    print(f'array3_y:    {array3_y}')
    print(f'array3_z:    {array3_z}')
    print()

    array3_E, array3_N, array3_U = ecef2enu_llaRef(array_lat, array_long, array_a, array3_x, array3_y, array3_z, ell=ellipsoid_wgs84, deg=True)

    print(f'Get the cordinates in ENU from ecef reference system.')
    print(f'array3_E:    {array3_E}')
    print(f'array3_N:    {array3_N}')
    print(f'array3_U:    {array3_U}')
    print()

    ##  ##

####  ####

if __name__=="__main__":

    main()

# End of document: coordinate_systems.py