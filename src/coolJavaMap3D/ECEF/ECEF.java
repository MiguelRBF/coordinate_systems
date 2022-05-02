// --- Origin ECEF coordinate system ---
//--------------------------------------------
// Module name:      ECEF.java
// Created by:       MiguelRBF
//--------------------------------------------

/*
This module was created to transforms from ECEF 
(earth-centered, earth-fixed) frame to others.
*/

// Package definition
package ECEF;

import ellipsoidDefinition.Ellipsoid;

public class ECEF {

    // --- Class atributes ---
    // Input x coordinate
    public double x;
    // Input y coordinate
    public double y;
    // Input z coordinate
    public double z;
    
    // Input ellipsoid
    public Ellipsoid ell;
    // Input degrees. If true, input is given in degrees.
    public boolean deg;

    // define intermediate variables
    private double r2, r, E2, F, G, c, s, P, Q, ro, tmp, U, V, zo;

    // Output ecef2lla method
    // Output latitude
    public double lat;
    // Output longitude
    public double lon;
    // Output altitude
    public double alt;
    
    // ---  ---

    // Class constructor
    public ECEF(double x_coordinate, double y_coordinate, double z_coordinate, Ellipsoid ellipsoid, boolean degrees){

        // Define latitude, longitude and altitude
        x = x_coordinate;
        y = y_coordinate;
        z = z_coordinate;

        // Define the ellipsoid model to be used
        ell = ellipsoid;

        // Define the type of output argument
        deg = degrees;
        
    }

    // Define ecef2lla method
    public void ecef2lla(){

        /*
        This function was created to change between ECEF coordinate system to 
        geodetic of specified ellipsoid (default WGS-84) coordinate system 
        (longitude, latitude, height).

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
        
        ell : Ellipsoid
            reference ellipsoid
        deg : bool
            degrees input/output  (False: radians in/out)

        Returns
        -------
        lat
            target geodetic latitude
        lon
            target geodetic longitude
        alt
            target altitude above geodetic ellipsoid (meters)
        */

        this.r2 = Math.pow(x,2)+Math.pow(y,2);
        this.r = Math.sqrt(this.r2);
        this.E2 = Math.pow(ell.a,2) - Math.pow(ell.b,2);
        this.F = 54*Math.pow(ell.b,2)*Math.pow(z,2);
        this.G = this.r2 + (1-ell.e2)*Math.pow(z,2) - ell.e2*this.E2;
        this.c = (ell.e2*ell.e2*this.F*this.r2)/(this.G*this.G*this.G);
        this.s = Math.pow( 1 + c + Math.sqrt(this.c*this.c + 2*this.c), 1/3 );
        this.P = this.F/(3*Math.pow(this.s+1.0/this.s+1.0, 2)*this.G*this.G);
        this.Q = Math.sqrt(1.0+2*ell.e2*ell.e2*this.P);
        this.ro = -(ell.e2*this.P*this.r)/(1+this.Q) + Math.sqrt((ell.a*ell.a/2)*(1+1./this.Q) - ((1-ell.e2)*this.P*Math.pow(this.z, 2))/(this.Q*(1+this.Q)) - this.P*this.r2/2);
        this.tmp = Math.pow(r - ell.e2*ro, 2);
        this.U = Math.sqrt( tmp + Math.pow(z,2) );
        this.V = Math.sqrt( tmp + (1-ell.e2)*Math.pow(z,2) );
        this.zo = (Math.pow(ell.b,2)*z)/(ell.a*V);

        // Now get the final coordinates: longitude, latitude and altitude
        lat = Math.atan((z+ell.ep2*zo)/r);
        lon = Math.atan2(y, x);
        alt = U*(1 - Math.pow(ell.b,2)/(ell.a*V));

        // If degres is wanted as output
        if (deg){
            // Convert longitude-latitude units from degrees to radians
            lat = lat*180.0/Math.PI;
            lon = lon*180.0/Math.PI;
        }
    }
    
}
