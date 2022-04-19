# --- Origin LLA coordinate system ---
#--------------------------------------------
# Module name:      lla.py
# Created by:       MiguelRBF
#--------------------------------------------
'''
This module was created to transforms from LLA 
(Latitude Longitude Altitude) frame to others.
'''

#### IMPORT STANDARD LIBRARIES ####
from math import pi

####  ####

#### IMPORT DOWNLOADED LIBRARIES ####
import numpy as np

####  ####

#### IMPORT MODULES ####
from .ellipsoid import Ellipsoid

####  ####

#### VARIABLE DEFINITION ####

# The __all__ tells the semantically “public” names from the module.
# If there is a name in __all__, the users are expected to use it, 
# and they can expect that it will not change.
# https://appdividend.com/2021/05/09/what-is-python-__all__-and-how-to-use-it/
__all__ = [
    "lla2ecef"
]

####  ####

#### FUNCTIONS DEFINITION ####

def lla2ecef(
    lat: np.float64,
    long: np.float64,
    alt: np.float64,
    ell: Ellipsoid = None,
    deg: bool = True
    ):
    '''
    Convert lat, long, altitude in geodetic of specified ellipsoid (default WGS-84)
    to ECEF X,Y,Z. Longitude and latitude can be given in decimal degrees or radians 
    (default decimal degrees). Altitude must be given in meters.

    np arrays can be given as inputs.

    Equations taken from:
    http://wiki.gis.com/wiki/index.php/Geodetic_system

    Parameters
    ----------
    lat
        target geodetic latitude
    lon
        target geodetic longitude
    alt
        target altitude above geodetic ellipsoid (meters)
    
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

    # If no ellipsoid is defined define the default ellipsoid (WGS84)
    if ell is None:
        ell = Ellipsoid()

    # If degres is wanted as output
    if deg:
        # Convert longitude-latitude units from degrees to radians
        lat = lat*pi/180
        long = long*pi/180

    # Compute chi parameter
    chi = np.sqrt(1-ell.e2*(np.sin(lat))**2)

    # Compute x, y and z coordinates
    x = (ell.a/chi +alt)*np.cos(lat)*np.cos(long)
    y = (ell.a/chi +alt)*np.cos(lat)*np.sin(long)
    z = (ell.a*(1-ell.e2)/chi + alt)*np.sin(lat)

    return x, y, z

####  ####

# End of document: lla.py