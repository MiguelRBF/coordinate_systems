# --- Minimal class for planetary ellipsoids ---
#--------------------------------------------
# Module name:      ellipsoid.py
# Created by:       geospace-code/MiguelRBF
#--------------------------------------------
'''
This module was created to transforms from LLH 
(Latitude Longitude Height) frame to others.
'''

#### IMPORT STANDARD LIBRARIES ####
from math import pi
from math import sqrt

####  ####

#### IMPORT DOWNLOADED LIBRARIES ####

####  ####

#### IMPORT MODULES ####

####  ####

#### VARIABLE DEFINITION ####

####  ####

#### FUNCTIONS DEFINITION ####

####  ####

#### CLASS DEFINITION ####
class Ellipsoid:
    """
    Class adapted from geospace-code
    generate reference ellipsoid parameters
    https://en.wikibooks.org/wiki/PROJ.4#Spheroid
    https://nssdc.gsfc.nasa.gov/planetary/factsheet/index.html
    as everywhere else in this program, distance units are METERS

    Ellipsoid defining parameters:
    a = semimajor_axis
    f = (first) flattening

    Ellipsoid derived geometric constants:
    b = semiminor_axis = a·(1-f)
    e2 = (first) eccentricity squared = (2-f)·f
    ep2 = second eccentricity squared = f·(2-f)/(1-f)^2
    fppp = third flattening = (a-b)/(a+b)

    """

    def __init__(self, model: str = "wgs84"):
        """
        feel free to suggest additional ellipsoids
        Parameters
        ----------
        model : str
                name of ellipsoid
        """

        # Create ellipsoid defining parameters
        if model == "wgs84":
            """https://en.wikipedia.org/wiki/World_Geodetic_System#WGS84"""
            self.a = 6378137.0
            self.f = 1/298.257223563
            self.b = self.a*(1-self.f)
        elif model == "wgs72":
            self.a = 6378135.0
            self.b = 6356750.52001609
        elif model == "grs80":
            """https://en.wikipedia.org/wiki/GRS_80"""
            self.a = 6378137.0
            self.b = 6356752.31414036
        elif model == "clarke1866":
            self.a = 6378206.4
            self.b = 6356583.8
        elif model == "mars":
            """
            https://tharsis.gsfc.nasa.gov/geodesy.html
            """
            self.a = 3396900.0
            self.b = 3376097.80585952
        elif model == "moon":
            self.a = 1738000.0
            self.b = self.a
        elif model == "venus":
            self.a = 6051000.0
            self.b = self.a
        elif model == "jupiter":
            self.a = 71492000.0
            self.b = 66770054.3475922
        elif model == "io":
            """
            https://doi.org/10.1006/icar.1998.5987
            """
            self.a = 1829.7
            self.b = 1815.8
        elif model == "pluto":
            self.a = 1187000.0
            self.b = self.a
        else:
            raise NotImplementedError(
                f"{model} model not implemented, let us know and we will add it (or make a pull request)"
            )

        # In wgs84 the flattening is a defining parameter. In the other ellipsoids the semiminor_axis
        # is the second defining parameter.
        if model != "wgs84":
            self.f = (self.a - self.b) / self.a

        # Create the rest of the ellipsoid derived geometric constants
        self.e2 = 2 * self.f - self.f ** 2
        self.ep2 = self.f*(2-self.f)/(1-self.f)**2
        self.fppp = (self.a - self.b) / (self.a + self.b)

####  ####