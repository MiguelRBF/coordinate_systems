// --- Origin LLA coordinate system ---
//--------------------------------------------
// Module name:      LLA.java
// Created by:       MiguelRBF
//--------------------------------------------

/*
This module was created to transforms from LLA 
(Latitude Longitude Altitude) frame to others.
*/

// Package definition
package LLA;

import ellipsoidDefinition.Ellipsoid;

public class LLA {

    // --- Class atributes ---
    // Input latitude
    public double lat;
    // Input longitude
    public double lon;
    // Input altitude
    public double alt;
    // Input ellipsoid
    public Ellipsoid ell;
    // Input degrees. If true, input is given in degrees.
    public boolean deg;

    // define intermediate variables
    private double chi;

    // Output lla2ecef method
    // Output x coordinate
    public double x;
    // Output y coordinate
    public double y;
    // Output z coordinate
    public double z;
    // ---  ---

    // Class constructor
    public LLA(double latitude, double longitude, double altitude, Ellipsoid ellipsoid, boolean degrees){

        // Define latitude, longitude and altitude
        lat = latitude;
        lon = longitude;
        alt = altitude;

        // Define the ellipsoid model to be used
        ell = ellipsoid;

        // Define the type of input argument
        deg = degrees;
        
    }

    // Define lla2ecef method
    public void lla2ecef(){

        /*
        This method converts lat, long, altitude in geodetic of specified 
        to ECEF X,Y,Z. Longitude and latitude can be given in decimal degrees or radians 
        (default decimal degrees). Altitude must be given in meters.

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
        
        ell : Ellipsoid
            reference ellipsoid
        deg : bool
            degrees input/output  (False: radians in/out)

        Returns
        -------
        x
            target x ECEF coordinate (meters)
        y
            target y ECEF coordinate (meters)
        z
            target z ECEF coordinate (meters)
        */

        // If degres is wanted as input
        if (deg){
            // Convert longitude-latitude units from degrees to radians
            lat = lat*Math.PI/180.0;
            lon = lon*Math.PI/180.0;
        }

        // Compute chi parameter
        this.chi = Math.sqrt(1-ell.e2*Math.pow(Math.sin(lat), 2));

        this.x = (ell.a/chi +alt)*Math.cos(lat)*Math.cos(lon);
        this.y = (ell.a/chi +alt)*Math.cos(lat)*Math.sin(lon);
        this.z = (ell.a*(1-ell.e2)/this.chi + alt)*Math.sin(lat);
    }
    
}
