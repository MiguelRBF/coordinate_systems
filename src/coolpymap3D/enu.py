# --- Origin ENU coordinate system ---
#--------------------------------------------
# Module name:      enu.py
# Created by:       MiguelRBF
#--------------------------------------------
'''
This module was created to transforms from ENU 
(East North Up) frame to others.
'''

#### IMPORT STANDARD LIBRARIES ####
from math import pi

####  ####

#### IMPORT DOWNLOADED LIBRARIES ####
import numpy as np

####  ####

#### IMPORT MODULES ####
from .ellipsoid import Ellipsoid
from .ecef import ecef2llh
from .lla import lla2ecef

####  ####

#### VARIABLE DEFINITION ####

# The __all__ tells the semantically “public” names from the module.
# If there is a name in __all__, the users are expected to use it, 
# and they can expect that it will not change.
# https://appdividend.com/2021/05/09/what-is-python-__all__-and-how-to-use-it/
__all__ = [
    "enu2ecef_ecefRef",
    "enu2ecef_llaRef"
]

####  ####

#### FUNCTIONS DEFINITION ####

def enu2ecef_ecefRef(
    refX: np.float64,
    refY: np.float64,
    refZ: np.float64,
    e: np.float64,
    n: np.float64,
    u: np.float64):
    '''This function convert local east, north, up coordinates (labeled e, n, u) to ECEF coordinates.

    A reference point in ECEF coordinates (x, y, z - refX, refY, refZ)
    must be given. All distances are in metres.

    np arrays can be given as inputs.

    Equations taken from:
    http://wiki.gis.com/wiki/index.php/Geodetic_system

    Parameters
    ----------
    e
        target east ENU coordinate (meters)
    n
        target north ENU coordinate (meters)
    u
        target up ENU coordinate (meters)
    refX
        reference x ECEF coordinate (meters)
    refY
        reference y ECEF coordinate (meters)
    refZ
        reference z ECEF coordinate (meters)

    Returns
    -------
    x
        target x ECEF coordinate (meters)
    y
        target y ECEF coordinate (meters)
    z
        target z ECEF coordinate (meters)
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

def enu2ecef_llaRef(
    refLat: np.float64,
    refLong: np.float64,
    refH: np.float64,
    e: np.float64,
    n: np.float64,
    u: np.float64,
    ell: Ellipsoid = None,
    deg: bool = True
    ):
    '''This function convert local east, north, up coordinates (labeled e, n, u)
    to ECEF coordinates.

    A reference point in geodetic coordinate system
    (latitude, longitude, height - refLat, refLong, refH)
    must be given. Longitude and latitude can be given in decimal degrees
    or radians (default decimal degrees). All distances are in metres.

    np arrays can be given as inputs.

    Equations taken from:
    http://wiki.gis.com/wiki/index.php/Geodetic_system

    Parameters
    ----------
    e
        target east ENU coordinate (meters)
    n
        target north ENU coordinate (meters)
    u
        target up ENU coordinate (meters)
    refX
        reference x ECEF coordinate (meters)
    refY
        reference y ECEF coordinate (meters)
    refZ
        reference z ECEF coordinate (meters)
    ell : Ellipsoid, optional
          reference ellipsoid
    deg : bool, optional
          degrees input/output  (False: radians in/out)
    
    Returns
    -------
    x
        target x ECEF coordinate (meters)
    y
        target y ECEF coordinate (meters)
    z
        target z ECEF coordinate (meters)
    '''

    # First find reference location in ECEF coordinates
    refX, refY, refZ = lla2ecef(refLat, refLong, refH, ell, deg)

    # Compute ecef coordinates
    x = -np.sin(refLong)*e - np.cos(refLong)*np.sin(refLat)*n + np.cos(refLong)*np.cos(refLat)*u + refX
    y = np.cos(refLong)*e - np.sin(refLong)*np.sin(refLat)*n + np.cos(refLat)*np.sin(refLong)*u + refY
    z = np.cos(refLat)*n + np.sin(refLat)*u + refZ

    return x, y, z

####  ####

# End of document: enu.py