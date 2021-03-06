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
import MatVec.MatVec;

public class ECEF {

    // --- Class attributes ---
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

        // Define x , y, z object attributes coordinates
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

        // If the reference coordinates are given in degrees
        if (deg){
            // Convert the reference latitude and longitude into radians
            refLat = refLat*Math.PI/180.0;
            refLon = refLon*Math.PI/180.0;
        }

        // Compute ENU coordinates
        enu[0] = -Math.sin(refLon)*(x-refXYZ[0]) + Math.cos(refLon)*(y-refXYZ[1]);
        enu[1] = -Math.sin(refLat)*Math.cos(refLon)*(x-refXYZ[0]) - Math.sin(refLat)*Math.sin(refLon)*(y-refXYZ[1]) + Math.cos(refLat)*(z-refXYZ[2]);
        enu[2] = Math.cos(refLat)*Math.cos(refLon)*(x-refXYZ[0]) + Math.cos(refLat)*Math.sin(refLon)*(y-refXYZ[1]) + Math.sin(refLat)*(z-refXYZ[2]);

        // Return output coordinates
        return enu;
    }

    // Define ecef2body method
    static public double[] ecef2body(double[] xyz, double[] xyzOb, double[][] ijkb){
        /*
        This function was created to change between ecef
	    to Body coordinate system.

	    Parameters
	    ----------
	    x = xyz[0]
        	target x ecef coordinate (meters)
	    y = xyz[1]
        	target y ecef coordinate (meters)
	    z = xyz[1]
        	target z ecef coordinate (meters)

	    xOb = xyzOb[0]
        	x body coordinate origin (ecef reference, meters)
	    yOb = xyzOb[1]
        	y body coordinate origin (ecef reference, meters)
	    zOb = xyzOb[2]
        	z body coordinate origin (ecef reference, meters)

	    ib = ijkb[:][0]
        	x body axis unitary vector (ecef reference, meters)
	    jb = ijkb[:][1]
        	y body axis unitary vector (ecef reference, meters)
	    kb = ijkb[:][2]
        	z body axis unitary vector (ecef reference, meters)

	    Returns
	    -------
	    xb = xyzb[0]
        	target x Body coordinate (meters)
	    yb = xyzb[1]
        	target y Body coordinate (meters)
	    zb = xyzb[2]
        	target z Body coordinate (meters)

	    Ob_P = inverse(R[??]) * (Oecef_P-Oecef_Ob) = Rinv * diff_OeP_OeOb = Rinv * (xyz - xyzOb)
        */

        // Define output method parameters
        double[] xyzb = new double[]{0.0, 0.0, 0.0};

        // Define inverse(R[??])
        double[][] Rinv = {{ijkb[0][0], ijkb[1][0], ijkb[2][0]},
						   {ijkb[0][1], ijkb[1][1], ijkb[2][1]},
						   {ijkb[0][2], ijkb[1][2], ijkb[2][2]}};

        // Initialize intermediate variables
        double[] diff_OeP_OeOb = new double[]{0.0, 0.0, 0.0};

        //  Get the difference between OeP (P coordinates in ecef reference) and
	    // OeOb (vector from ecef origin to body origin).
	    diff_OeP_OeOb[0] = xyz[0] - xyzOb[0];
	    diff_OeP_OeOb[1] = xyz[1] - xyzOb[1];
	    diff_OeP_OeOb[2] = xyz[2] - xyzOb[2];

        // Get the final coordinates in body reference
	    xyzb = MatVec.multiplyMatVec(Rinv, diff_OeP_OeOb);

        // Return output coordinates
        return xyzb;
    }

    // Define llaWrite method
    public void llaWrite(double lat_coordinate, double lon_coordinate, double alt_coordinate){
        /*
        Method to write output coordinates into the object attributes
        */

        // Define x , y, z object attributes coordinates
        atri_lat = lat_coordinate;
        atri_lon = lon_coordinate;
        atri_alt = alt_coordinate;
    }

    // Define enuWrite method
    public void enuWrite(double e_coordinate, double n_coordinate, double u_coordinate){
        /*
        Method to write output coordinates into the object attributes
        */

        // Define x , y, z object attributes coordinates
        atri_e = e_coordinate;
        atri_n = n_coordinate;
        atri_u = u_coordinate;
    }
    
}
