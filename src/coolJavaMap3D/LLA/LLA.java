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

// Import used packages
import ellipsoidDefinition.Ellipsoid;

public class LLA {

    // --- Class attributes ---
    // Input latitude
    public double atri_lat;
    // Input longitude
    public double atri_lon;
    // Input altitude
    public double atri_alt;
    // Input ellipsoid
    public Ellipsoid atri_ell;
    // Input degrees. If true, input is given in degrees.
    public boolean atri_deg;

    // Output lla2ecef method
    // Output x coordinate
    public double atri_x;
    // Output y coordinate
    public double atri_y;
    // Output z coordinate
    public double atri_z;
    // ---  ---

    // Class constructor
    public LLA(double latitude, double longitude, double altitude, Ellipsoid ellipsoid, boolean degrees){

        // Define latitude, longitude and altitude
        atri_lat = latitude;
        atri_lon = longitude;
        atri_alt = altitude;

        // Define the ellipsoid model to be used
        atri_ell = ellipsoid;

        // Define the type of input argument
        atri_deg = degrees;
        
    }

    // Define lla2ecef method
    static public double[] lla2ecef(double lat, double lon, double alt, Ellipsoid ell, boolean deg){

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

        // Define output parameter
        double[] xyz = new double[]{0.0, 0.0, 0.0};

        // Define intermediate variables
        double radLat, radLon;
        double chi;

        // If degres is wanted as input
        if (deg){
            // Convert longitude-latitude units from degrees to radians
            radLat = lat*Math.PI/180.0;
            radLon = lon*Math.PI/180.0;
        } else{
            radLat = lat;
            radLon = lon;
        }

        // Compute chi parameter
        chi = Math.sqrt(1-ell.e2*Math.pow(Math.sin(radLat), 2));

        xyz[0] = (ell.a/chi +alt)*Math.cos(radLat)*Math.cos(radLon);
        xyz[1] = (ell.a/chi +alt)*Math.cos(radLat)*Math.sin(radLon);
        xyz[2] = (ell.a*(1-ell.e2)/chi + alt)*Math.sin(radLat);

        // Return output coordinates
        return xyz;
    }

    // Define xyzWrite method
    public void xyzWrite(double x_coordinate, double y_coordinate, double z_coordinate){
        /*
        Method to write output coordinates into the object attributes
        */

        // Define x , y, z object attributes coordinates
        atri_x = x_coordinate;
        atri_y = y_coordinate;
        atri_z = z_coordinate;
    }
    
}
