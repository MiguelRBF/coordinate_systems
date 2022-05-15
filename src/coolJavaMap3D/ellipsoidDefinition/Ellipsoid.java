// --- Class for planetary ellipsoids ---
//--------------------------------------------
// Module name:      ellipsoid.java
// Created by:       MiguelRBF
//--------------------------------------------

/*
This module was created to define the required 
ellipsoid for the LLA reference frames.
*/

// Package definition
package ellipsoidDefinition;

public class Ellipsoid{

    /*
    Class description:

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
    */
    
    // Class attributes
    public double a;
    public double f;
    public double b;
    public double e2;
    public double ep2;

    // Class constructor
    public Ellipsoid(String model){

        // Create ellipsoid defining parameters
        if (model == "wgs84"){
            // https://en.wikipedia.org/wiki/World_Geodetic_System#WGS84
            a = 6378137.0;
            f = 1/298.257223563;
            b = a*(1-f);
        } else if (model == "wgs72"){
            a = 6378135.0;
            b = 6356750.52001609;
        } else if (model == "grs80"){
            // https://en.wikipedia.org/wiki/GRS_80"""
            a = 6378137.0;
            b = 6356752.31414036;
        } else if (model == "clarke1866"){
            a = 6378206.4;
            b = 6356583.8;
        } else if ( model == "mars"){
            // https://tharsis.gsfc.nasa.gov/geodesy.html
            a = 3396900.0;
            b = 3376097.80585952;
        } else if (model == "moon"){
            a = 1738000.0;
            b = a;
        } else if (model == "venus"){
            a = 6051000.0;
            b = a;
        } else if (model == "jupiter"){
            a = 71492000.0;
            b = 66770054.3475922;
        } else if (model == "io"){
            // https://doi.org/10.1006/icar.1998.5987
            a = 1829.7;
            b = 1815.8;
        } else if (model == "pluto"){
            a = 1187000.0;
            b = a;
        }else {
            throw new java.lang.RuntimeException("model not implemented, let us know and we will add it");
        }

        // In wgs84 the flattening is a defining parameter. In the other ellipsoids the semiminor_axis
        // is the second defining parameter.
        if (model != "wgs84"){
            f = (a - b) / a;
        }

        // Create the rest of the ellipsoid derived geometric constants
        e2 = 2 * f - Math.pow(f, 2);
        ep2 = f*(2-f)/Math.pow(1-f, 2);
    }

}