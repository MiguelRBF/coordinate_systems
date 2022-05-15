# Copyright (c) 2014-2018 Michael Hirsch, Ph.D.
# Copyright (c) 2013, Felipe Geremia Nievinski
# Copyright (c) 2004-2007 Michael Kleder

# --- Some utils functions ---
#--------------------------------------------
# Module name:      utils.py
# Created by:       geospace-code/MiguelRBF
#--------------------------------------------

"""Some utility functions. All assume radians."""

#### IMPORT STANDARD LIBRARIES ####
from __future__ import annotations
from math import pi
####  ####

#### IMPORT MODULES ####
from .ellipsoid import Ellipsoid
####  ####

#### IMPORT DOWNLOADED LIBRARIES ####
try:
    from numpy import hypot, cos, sin, arctan2 as atan2, radians, asarray, sign
except ImportError:
    from math import atan2, hypot, cos, sin, radians  # type: ignore

    def sign(x) -> float:  # type: ignore
        """signum function"""
        if x < 0:
            y = -1.0
        elif x > 0:
            y = 1.0
        else:
            y = 0.0

        return y
####  ####

__all__ = ["cart2pol", "pol2cart", "cart2sph", "sph2cart", "sign"]

#### FUNCTIONS DEFINITION ####

def cart2pol(x, y) -> tuple:
    """Transform Cartesian to polar coordinates"""
    return atan2(y, x), hypot(x, y)


def pol2cart(theta, rho) -> tuple:
    """Transform polar to Cartesian coordinates"""
    return rho * cos(theta), rho * sin(theta)


def cart2sph(x, y, z) -> tuple:
    """Transform Cartesian to spherical coordinates"""
    hxy = hypot(x, y)
    r = hypot(hxy, z)
    el = atan2(z, hxy)
    az = atan2(y, x)
    return az, el, r


def sph2cart(az, el, r) -> tuple:
    """Transform spherical to Cartesian coordinates"""
    rcos_theta = r * cos(el)
    x = rcos_theta * cos(az)
    y = rcos_theta * sin(az)
    z = r * sin(el)
    return x, y, z


def sanitize(lat, ell: Ellipsoid | None, deg: bool) -> tuple:

    if ell is None:
        ell = Ellipsoid()

    try:
        lat = asarray(lat)
    except NameError:
        pass

    if deg:
        lat = radians(lat)

    try:
        if (abs(lat) > pi / 2).any():  # type: ignore
            raise ValueError("-pi/2 <= latitude <= pi/2")
    except AttributeError:
        if abs(lat) > pi / 2:  # type: ignore
            raise ValueError("-pi/2 <= latitude <= pi/2")

    return lat, ell

####  ####

# End of document: utils.py