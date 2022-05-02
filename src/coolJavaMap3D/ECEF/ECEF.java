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

// Import used packages
import ellipsoidDefinition.Ellipsoid;
import LLA.LLA;

public class ECEF {

    // --- Class atributes ---
    // Input x coordinate
    public double atri_x;
    // Input y coordinate
    public double atri_y;
    // Input z coordinate
    public double atri_z;
    
    // Input ellipsoid
    public Ellipsoid atri_ell;
    // Input degrees. If true, input is given in degrees.
    public boolean atri_deg;

    // Output ecef2lla method
    // Output latitude
    public double atri_lat;
    // Output longitude
    public double atri_lon;
    // Output altitude
    public double atri_alt;

    // Output ecef2enu methods
    // Output latitude
    public double atri_e;
    // Output longitude
    public double atri_n;
    // Output altitude
    public double atri_u;
    
    // ---  ---

    // Class constructor
    public ECEF(double x_coordinate, double y_coordinate, double z_coordinate, Ellipsoid ellipsoid, boolean degrees){

        // Define x , y, z object atributes coordinates
        atri_x = x_coordinate;
        atri_y = y_coordinate;
        atri_z = z_coordinate;

        // Define the ellipsoid model to be used
        atri_ell = ellipsoid;

        // Define the type of output argument
        atri_deg = degrees;
        
    }

    // Define ecef2lla method
    static public double[] ecef2lla(double x, double y, double z, Ellipsoid ell, boolean deg){

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

        // Define output parameters
        double[] lla = new double[]{0.0, 0.0, 0.0};

        // Define intermediate variables
        double r2, r, E2, F, G, c, s, P, Q, ro, tmp, U, V, zo;

        r2 = Math.pow(x,2)+Math.pow(y,2);
        r2 = x*x+y*y;
        r = Math.sqrt(r2);
        E2 = Math.pow(ell.a,2) - Math.pow(ell.b,2);
        F = 54.0*Math.pow(ell.b,2)*Math.pow(z,2);
        G = r2 + (1-ell.e2)*Math.pow(z,2) - ell.e2*E2;
        c = (ell.e2*ell.e2*F*r2)/(G*G*G);
        s = Math.pow( 1.0 + c + Math.sqrt(c*c + 2*c), 1.0/3.0 );
        P = F/(3*Math.pow(s+1.0/s+1.0, 2)*G*G);
        Q = Math.sqrt(1.0+2*ell.e2*ell.e2*P);
        ro = -(ell.e2*P*r)/(1+Q) + Math.sqrt((ell.a*ell.a/2)*(1+1./Q) - ((1-ell.e2)*P*Math.pow(z, 2))/(Q*(1+Q)) - P*r2/2);
        tmp = Math.pow(r - ell.e2*ro, 2);
        U = Math.sqrt( tmp + Math.pow(z,2) );
        V = Math.sqrt( tmp + (1-ell.e2)*Math.pow(z,2) );
        zo = (Math.pow(ell.b,2)*z)/(ell.a*V);

        // Now get the final coordinates: longitude, latitude and altitude
        lla[0] = Math.atan((z+ell.ep2*zo)/r);
        lla[1] = Math.atan2(y, x);
        lla[2] = U*(1 - Math.pow(ell.b,2)/(ell.a*V));

        // If degres is wanted as output
        if (deg){
            // Convert longitude-latitude units from degrees to radians
            lla[0] = lla[0]*180.0/Math.PI;
            lla[1] = lla[1]*180.0/Math.PI;
        }

        // Return output coordinates
        return lla;
    }

    // Define ecef2enu_ecefRef method
    static public double[] ecef2enu_ecefRef(double refX, double refY, double refZ, double x, double y, double z, Ellipsoid ell){
        /*
        This function converts ECEF coordinates to local east, north, up coordinates (ENU).

        A reference point in ECEF coordinates (x, y, z - refX, refY, refZ)
        must be given. All distances are in meters.

        Equations taken from:
        http://wiki.gis.com/wiki/index.php/Geodetic_system

        Parameters
        ----------
        refX
            reference x ECEF coordinate (meters)
        refY
            reference y ECEF coordinate (meters)
        refZ
            reference z ECEF coordinate (meters)
        x
            target x ECEF coordinate (meters)
        y
            target y ECEF coordinate (meters)
        z
            target z ECEF coordinate (meters)
        ell : Ellipsoid, optional
            reference ellipsoid

        Returns
        -------
        e
            target east ENU coordinate (meters)
        n
            target north ENU coordinate (meters)
        u
            target up ENU coordinate (meters)
        */
        // Define output parameters
        double[] enu = new double[]{0.0, 0.0, 0.0};

        // Define internal method parameters
        double[] refLLA = new double[]{0.0, 0.0, 0.0};

        // First find reference location in LLA coordinates (radians)
        refLLA =  ecef2lla(refX, refY, refZ, ell, false);

        // Compute ENU coordinates
        enu[0] = -Math.sin(refLLA[1])*(x-refX) + Math.cos(refLLA[1])*(y-refY);
        enu[1] = -Math.sin(refLLA[0])*Math.cos(refLLA[1])*(x-refX) - Math.sin(refLLA[0])*Math.sin(refLLA[1])*(y-refY) + Math.cos(refLLA[0])*(z-refZ);
        enu[2] = Math.cos(refLLA[0])*Math.cos(refLLA[1])*(x-refX) + Math.cos(refLLA[0])*Math.sin(refLLA[1])*(y-refY) + Math.sin(refLLA[0])*(z-refZ);

        // Return output coordinates
        return enu;
    }

    // Define ecef2enu_ecefRef method
    static public double[] ecef2enu_llaRef(double refLat, double refLon, double refAlt, double x, double y, double z, Ellipsoid ell, boolean deg){
        /*
        This function convert ECEF coordinates to local east, north, up coordinates.

        A reference point in geodetic coordinate system 
        (latitude, longitude, height - refLat, refLon, refAlt)
        must be given. All distances are in meters.

        Equations taken from:
        http://wiki.gis.com/wiki/index.php/Geodetic_system

        Parameters
        ----------
        
        refLat
            reference geodetic latitude
        refLong
            reference geodetic longitude
        refAlt
            reference altitude above geodetic ellipsoid (meters)
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
        e
            target east ENU coordinate (meters)
        n
            target north ENU coordinate (meters)
        u
            target up ENU coordinate (meters)
        */
        // Define output parameters
        double[] enu = new double[]{0.0, 0.0, 0.0};

        // Define internal method parameters
        double[] refXYZ = new double[]{0.0, 0.0, 0.0};

        // // Create lla_coordinates coordinate system object
        // LLA lla_coordinates = new LLA(refLat, refLon, refAlt, ell, deg);

        // First find reference location in LLA coordinates (radians)
        // lla2ecef is static
        refXYZ =  LLA.lla2ecef(refLat, refLon, refAlt, ell, deg);

        // Compute ENU coordinates
        enu[0] = -Math.sin(refLon)*(x-refXYZ[0]) + Math.cos(refLon)*(y-refXYZ[1]);
        enu[1] = -Math.sin(refLat)*Math.cos(refLon)*(x-refXYZ[0]) - Math.sin(refLat)*Math.sin(refLon)*(y-refXYZ[1]) + Math.cos(refLat)*(z-refXYZ[2]);
        enu[2] = Math.cos(refLat)*Math.cos(refLon)*(x-refXYZ[0]) + Math.cos(refLat)*Math.sin(refLon)*(y-refXYZ[1]) + Math.sin(refLat)*(z-refXYZ[2]);

        // Return output coordinates
        return enu;
    }

    // Define llaWrite method
    public void llaWrite(double lat_coordinate, double lon_coordinate, double alt_coordinate){
        /*
        Method to write output coordinates into the object atributes
        */

        // Define x , y, z object atributes coordinates
        atri_lat = lat_coordinate;
        atri_lon = lon_coordinate;
        atri_alt = alt_coordinate;
    }

    // Define enuWrite method
    public void enuWrite(double e_coordinate, double n_coordinate, double u_coordinate){
        /*
        Method to write output coordinates into the object atributes
        */

        // Define x , y, z object atributes coordinates
        atri_e = e_coordinate;
        atri_n = n_coordinate;
        atri_u = u_coordinate;
    }
    
}
