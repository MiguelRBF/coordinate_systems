# --- Involving ECI coordinate system ---
#--------------------------------------------
# Module name:      eci.py
# Created by:       geospace-code/MiguelRBF
#--------------------------------------------
'''
This module was created to do transformations 
involving ECI (earth-centered inertial) reference frame.
'''

#### IMPORT STANDARD LIBRARIES ####
# With __future__ module's inclusion, you can slowly be accustomed to incompatible changes 
# or to such ones introducing new keywords. E.g., for using context managers, you had to do
# from __future__ import with_statement in 2.5, as the with keyword was new and shouldn't
# be used as variable names any longer. In order to use with as a Python keyword in 
# Python 2.5 or older, you will need to use the import from above.
# https://stackoverflow.com/questions/7075082/what-is-future-in-python-used-for-and-how-when-to-use-it-and-how-it-works
from __future__ import annotations
from datetime import datetime

####  ####

#### IMPORT DOWNLOADED LIBRARIES ####
from numpy import array, sin, cos, column_stack, empty, atleast_1d
try:
    from astropy.coordinates import GCRS, ITRS, EarthLocation, CartesianRepresentation
    from astropy.time import Time
    import astropy.units as u
except ImportError:
    Time = None

####  ####

#### IMPORT MODULES ####
from .sidereal import greenwichsrt, juliandate

####  ####

#### VARIABLE DEFINITION ####

# The __all__ tells the semantically “public” names from the module.
# If there is a name in __all__, the users are expected to use it, 
# and they can expect that it will not change.
# https://appdividend.com/2021/05/09/what-is-python-__all__-and-how-to-use-it/
__all__ = ["eci2ecef", "ecef2eci"]

####  ####

#### FUNCTIONS DEFINITION ####

def R3(x: float):
    """Rotation matrix for ECI"""
    return array([[cos(x), sin(x), 0], [-sin(x), cos(x), 0], [0, 0, 1]])

def eci2ecef(x, y, z, time: datetime, *, use_astropy: bool = True) -> tuple:
    """
    Observer => Point  ECI  =>  ECEF
    J2000 frame
    Parameters
    ----------
    x : float
        ECI x-location [meters]
    y : float
        ECI y-location [meters]
    z : float
        ECI z-location [meters]
    time : datetime.datetime
        time of obsevation (UTC)
    use_astropy: bool, optional
        use AstroPy (much more accurate)
    Results
    -------
    x_ecef : float
        x ECEF coordinate
    y_ecef : float
        y ECEF coordinate
    z_ecef : float
        z ECEF coordinate
    """

    if use_astropy and Time is not None:
        gcrs = GCRS(CartesianRepresentation(x * u.m, y * u.m, z * u.m), obstime=time)
        itrs = gcrs.transform_to(ITRS(obstime=time))

        x_ecef = itrs.x.value
        y_ecef = itrs.y.value
        z_ecef = itrs.z.value
    else:
        x = atleast_1d(x)
        y = atleast_1d(y)
        z = atleast_1d(z)
        gst = atleast_1d(greenwichsrt(juliandate(time)))
        assert x.shape == y.shape == z.shape
        assert x.size == gst.size

        eci = column_stack((x.ravel(), y.ravel(), z.ravel()))
        ecef = empty((x.size, 3))
        for i in range(eci.shape[0]):
            ecef[i, :] = R3(gst[i]) @ eci[i, :].T

        x_ecef = ecef[:, 0].reshape(x.shape)
        y_ecef = ecef[:, 1].reshape(y.shape)
        z_ecef = ecef[:, 2].reshape(z.shape)

    return x_ecef, y_ecef, z_ecef

def ecef2eci(x, y, z, time: datetime, *, use_astropy: bool = True) -> tuple:
    """
    Point => Point   ECEF => ECI
    J2000 frame
    Parameters
    ----------
    x : float
        target x ECEF coordinate
    y : float
        target y ECEF coordinate
    z : float
        target z ECEF coordinate
    time : datetime.datetime
        time of observation
    use_astropy: bool, optional
        use AstroPy (much more accurate)
    Results
    -------
    x_eci : float
        x ECI coordinate
    y_eci : float
        y ECI coordinate
    z_eci : float
        z ECI coordinate
    """

    if use_astropy and Time is not None:
        itrs = ITRS(CartesianRepresentation(x * u.m, y * u.m, z * u.m), obstime=time)
        gcrs = itrs.transform_to(GCRS(obstime=time))
        eci = EarthLocation(*gcrs.cartesian.xyz)

        x_eci = eci.x.value
        y_eci = eci.y.value
        z_eci = eci.z.value
    else:
        x = atleast_1d(x)
        y = atleast_1d(y)
        z = atleast_1d(z)
        gst = atleast_1d(greenwichsrt(juliandate(time)))
        assert x.shape == y.shape == z.shape
        assert x.size == gst.size

        ecef = column_stack((x.ravel(), y.ravel(), z.ravel()))
        eci = empty((x.size, 3))
        for i in range(x.size):
            eci[i, :] = R3(gst[i]).T @ ecef[i, :]

        x_eci = eci[:, 0].reshape(x.shape)
        y_eci = eci[:, 1].reshape(y.shape)
        z_eci = eci[:, 2].reshape(z.shape)

    return x_eci, y_eci, z_eci

####  ####

# End of document: eci.py