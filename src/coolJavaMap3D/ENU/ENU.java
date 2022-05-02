// --- Origin ECEF coordinate system ---
//--------------------------------------------
// Module name:      ENU.java
// Created by:       MiguelRBF
//--------------------------------------------

// Package definition
package ENU;

// Import used packages
import ellipsoidDefinition.Ellipsoid;
import LLA.LLA;
import ECEF.ECEF;

public class ENU {

    // --- Class atributes ---
    
    // Input latitude
    public double atri_e;
    // Input longitude
    public double atri_n;
    // Input altitude
    public double atri_u;
    
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

    // Output enu2ecef methods
    // Output x coordinate
    public double atri_x;
    // Output y coordinate
    public double atri_y;
    // Output z coordinate
    public double atri_z;
    
    // ---  ---

    // Class constructor
    public ENU(double e_coordinate, double n_coordinate, double u_coordinate, Ellipsoid ellipsoid, boolean degrees){

        // Define x , y, z object atributes coordinates
        atri_e = e_coordinate;
        atri_n = n_coordinate;
        atri_u = u_coordinate;

        // Define the ellipsoid model to be used
        atri_ell = ellipsoid;

        // Define the type of output argument
        atri_deg = degrees;
        
    }

    // Define enu2ecef_ecefRef method
    static public double[] enu2ecef_ecefRef(double refX, double refY, double refZ, double e, double n, double u, Ellipsoid ell){
        /*
        This function converts local east, north, up coordinates (labeled e, n, u) to ECEF coordinates.

        A reference point in ECEF coordinates (x, y, z - refX, refY, refZ)
        must be given. All distances are in meters.

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
        */

        // Define output parameters
        double[] xyz = new double[]{0.0, 0.0, 0.0};

        // Define internal method parameters
        double[] refLLA = new double[]{0.0, 0.0, 0.0};
        double refLat, refLon;

        // First find reference location in LLA coordinates (radians)
        refLLA =  ECEF.ecef2lla(refX, refY, refZ, ell, false);

        // Save refLLA into intermediate variables
        refLat = refLLA[0];
        refLon = refLLA[1];

        // Compute ecef coordinates (x,y,x)
        xyz[0] = -Math.sin(refLon)*e - Math.cos(refLon)*Math.sin(refLat)*n + Math.cos(refLon)*Math.cos(refLat)*u + refX;
        xyz[1] = Math.cos(refLon)*e - Math.sin(refLon)*Math.sin(refLat)*n + Math.cos(refLat)*Math.sin(refLon)*u + refY;
        xyz[2] = Math.cos(refLat)*n + Math.sin(refLat)*u + refZ;

        // Return output coordinates
        return xyz;
    }

    // Define enu2ecef_ecefRef method
    static public double[] enu2ecef_llaRef(double refLat, double refLon, double refAlt, double e, double n, double u, Ellipsoid ell, boolean deg){
        /*
        This function converts local east, north, up coordinates (labeled e, n, u)
        to ECEF coordinates.

        A reference point in geodetic coordinate system
        (latitude, longitude, height - refLat, refLong, refA)
        must be given. Longitude and latitude can be given in decimal degrees
        or radians (default decimal degrees). All distances are in meters.

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

        // Define output parameters
        double[] xyz = new double[]{0.0, 0.0, 0.0};

        // Define internal method parameters
        double[] refXYZ = new double[]{0.0, 0.0, 0.0};

        // First find reference location in xyz coordinates (radians)
        refXYZ =  LLA.lla2ecef(refLat, refLon, refAlt, ell, deg);

        // If the reference coordinates are given in degrees
        if (deg){
            // Convert the reference latitude and longitude into radians
            refLat = refLat*Math.PI/180.0;
            refLon = refLon*Math.PI/180.0;
        }

        // Compute ecef coordinates (x,y,x)
        xyz[0] = -Math.sin(refLon)*e - Math.cos(refLon)*Math.sin(refLat)*n + Math.cos(refLon)*Math.cos(refLat)*u + refXYZ[0];
        xyz[1] = Math.cos(refLon)*e - Math.sin(refLon)*Math.sin(refLat)*n + Math.cos(refLat)*Math.sin(refLon)*u + refXYZ[1];
        xyz[2] = Math.cos(refLat)*n + Math.sin(refLat)*u + refXYZ[2];

        // Return output coordinates
        return xyz;
    }
    
}
