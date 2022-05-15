// --- COORDINATE SYSTEMS ---
//--------------------------------------------
// Module name:      coordinate_systems_java_example.java
// Created by:       MiguelRBF
//--------------------------------------------

/*
This module was created to manage the change between coordinate systems
*/

// Import used packages
import ellipsoidDefinition.Ellipsoid;
import LLA.LLA;
import ECEF.ECEF;
import ENU.ENU;
import BODY.BODY;

public class coordinate_systems_java_example {

    // --- Class attributes ---
    // - EXAMPLE 1 -
    // Define the ellipsoid model to be used
    static public String model = "wgs84";

    // Define Bern geodetic coordinates (WGS84: latitude, longitude, altitude)
    static public double[] llaBernCord = new double[]{46.94809, 7.44744, 549.0};
    static public double[] llaBernCordOut = new double[]{0.0, 0.0, 0.0};

    // Define Bern ecef coordinates (x, y , z)
    static public double[] xyzBernCord = new double[]{4325481.828902, 565424.238826, 4638228.339585};
    static public double[] xyzBernCordOut = new double[]{0.0, 0.0, 0.0};

    // Suppose a reference GNSS station in Bern with and ENU error of:
    // E=1.0m , N=0.798654m and U=1.6543m
    // Use as reference the Bern position

    // Define Bern station ecef coordinates (x, y , z)
    static public double[] enuStationBernCord = new double[]{1.0, 0.798654, 1.6543};
    static public double[] enuStationBernCordOut = new double[]{0.0, 0.0, 0.0};
    static public double[] xyzStationBernCordOut = new double[]{0.0, 0.0, 0.0};
    // -  -

    // - EXAMPLE 2 -

    // Define the rotation matrix R[θ]=ijkb
	static public double[][] ijkb = new double[][]{{0., 1., 0.},
                                                   {1., 0., 0.},
                                                   {0., 0., 1.}};

    // Define the target ecef coordinates
	static public double[] tar_xyz = new double[]{26600000., 10., 0.};

	// Define the body origin coordinates
	static public double[] xyzOb = new double[]{26600000., 0., 0.};

	// Initialize target body coordinates
	static public double[] tar_xyzb = new double[]{0, 0, 0};

    // -  -
    // ---  ---

    // Create main method
    public static void main(String[] args){

        // - EXAMPLE 1 -

        // Create ellipsoid object
        Ellipsoid ell = new Ellipsoid(model);

        // Show ellipsoid parameters
        System.out.println("Ellipsoid parameters:");
        String sf=String.format("semimajor_axis[m]: %.4f",ell.a);  
        System.out.println(sf);
        sf=String.format("semiminor_axis[m]: %.4f",ell.b);  
        System.out.println(sf);
        sf=String.format("First flattening: %.8f",ell.f);  
        System.out.println(sf);
        sf=String.format("First eccentricity squared: %.8f",ell.e2);  
        System.out.println(sf);
        sf=String.format("Second eccentricity squared: %.8f\n",ell.ep2);  
        System.out.println(sf);

        // Create lla_Bern_coordinates coordinate system object
        LLA lla_Bern_coordinates = new LLA(llaBernCord[0], llaBernCord[1], llaBernCord[2], ell, true);

        // Print Bern geodetic (WGS84) coordinates
        System.out.println("Bern geodetic (WGS84) coordinates:");
        sf=String.format("WGS84[°; °; m]: [%.8f; %.8f; %.8f]",llaBernCord[0],llaBernCord[1],llaBernCord[2]);  
        System.out.println(sf);

        // Compute Bern ecef coordinates from geodetic WGS84
        System.out.println("Compute Bern ecef coordinates from geodetic WGS84...\n");
        xyzBernCordOut = LLA.lla2ecef(llaBernCord[0], llaBernCord[1], llaBernCord[2], ell, true);

        // Print Bern ecef coordinates
        System.out.println("Bern ecef coordinates:");
        sf=String.format("xyz[m]: [%.8f; %.8f; %.8f]",xyzBernCordOut[0],xyzBernCordOut[1],xyzBernCordOut[2]);  
        System.out.println(sf);

        // Write output into object attributes
        lla_Bern_coordinates.xyzWrite(xyzBernCordOut[0], xyzBernCordOut[1], xyzBernCordOut[2]);

        // Bern ecef coordinates, object attributes
        System.out.println("Bern ecef coordinates, object attributes:");
        sf=String.format("xyz[m]: [%.8f; %.8f; %.8f]",lla_Bern_coordinates.atri_x, lla_Bern_coordinates.atri_y, lla_Bern_coordinates.atri_z);  
        System.out.println(sf);

        // Create xyz_Bern_coordinates coordinate system object
        ECEF xyz_Bern_coordinates = new ECEF(xyzBernCord[0], xyzBernCord[1], xyzBernCord[2], ell, true);

        // Print Input Bern ecef coordinates [m]
        System.out.println("Input Bern ecef coordinates [m]:");
        sf=String.format("xyz[m]: [%.8f; %.8f; %.8f]",xyzBernCord[0],xyzBernCord[1],xyzBernCord[2]);  
        System.out.println(sf);

        // Compute Bern geodetic WGS84 coordinates from ecef
        System.out.println("Compute Bern geodetic WGS84 coordinates from ecef...\n");
        llaBernCordOut = ECEF.ecef2lla(xyzBernCord[0], xyzBernCord[1], xyzBernCord[2], ell, true);

        // Print Bern ecef coordinates
        System.out.println("Bern geodetic (WGS84) coordinates:");
        sf=String.format("WGS84[°; °; m]: [%.8f; %.8f; %.8f]",llaBernCordOut[0],llaBernCordOut[1],llaBernCordOut[2]);  
        System.out.println(sf);

        // Write output into object attributes
        xyz_Bern_coordinates.llaWrite(llaBernCordOut[0], llaBernCordOut[1], llaBernCordOut[2]);

        // Create xyz_Bern_coordinates coordinate system object
        ENU enu_Bern_coordinates = new ENU(enuStationBernCord[0], enuStationBernCord[1], enuStationBernCord[2], ell, true);
        
        // Compute Bern station ecef coordinates from enu, ecef reference
        System.out.println("Compute Bern station ecef coordinates from enu, ecef reference...\n");
        xyzStationBernCordOut = ENU.enu2ecef_ecefRef(xyzBernCord[0], xyzBernCord[1], xyzBernCord[2], enuStationBernCord[0], enuStationBernCord[1], enuStationBernCord[2], ell);

        // Print Bern station ecef coordinates
        System.out.println("Bern station ecef coordinates:");
        sf=String.format("xyz[m]: [%.8f; %.8f; %.8f]",xyzStationBernCordOut[0],xyzStationBernCordOut[1],xyzStationBernCordOut[2]);  
        System.out.println(sf);

        // Write output into object attributes
        enu_Bern_coordinates.xyzWrite(xyzStationBernCordOut[0], xyzStationBernCordOut[1], xyzStationBernCordOut[2]);

        // Compute Bern station enu coordinates from ecef, ecef reference
        System.out.println("Compute Bern station enu coordinates from ecef, ecef reference...\n");
        enuStationBernCordOut = ECEF.ecef2enu_ecefRef(xyzBernCord[0], xyzBernCord[1], xyzBernCord[2], xyzStationBernCordOut[0], xyzStationBernCordOut[1], xyzStationBernCordOut[2], ell);

        // Print Bern station enu coordinates
        System.out.println("Bern station enu coordinates, ecef reference:");
        sf=String.format("enu[m]: [%.8f; %.8f; %.8f]",enuStationBernCordOut[0],enuStationBernCordOut[1],enuStationBernCordOut[2]);
        System.out.println(sf);  

        // Compute Bern station ecef coordinates from enu, lla reference
        System.out.println("Compute Bern station ecef coordinates from enu, lla reference...\n");
        xyzStationBernCordOut = ENU.enu2ecef_llaRef(llaBernCord[0], llaBernCord[1], llaBernCord[2], enuStationBernCord[0], enuStationBernCord[1], enuStationBernCord[2], ell, true);

        // Print Bern station ecef coordinates
        System.out.println("Bern station ecef coordinates:");
        sf=String.format("xyz[m]: [%.8f; %.8f; %.8f]",xyzStationBernCordOut[0],xyzStationBernCordOut[1],xyzStationBernCordOut[2]);
        System.out.println(sf); 

        // Write output into object attributes
        enu_Bern_coordinates.xyzWrite(xyzStationBernCordOut[0], xyzStationBernCordOut[1], xyzStationBernCordOut[2]);

        // Compute Bern station enu coordinates from ecef, lla reference
        System.out.println("Compute Bern station enu coordinates from ecef, lla reference...\n");
        enuStationBernCordOut = ECEF.ecef2enu_llaRef(llaBernCord[0], llaBernCord[1], llaBernCord[2], xyzStationBernCordOut[0], xyzStationBernCordOut[1], xyzStationBernCordOut[2], ell, true);

        // Print Bern station enu coordinates
        System.out.println("Bern station enu coordinates, lla reference:");
        sf=String.format("enu[m]: [%.8f; %.8f; %.8f]",enuStationBernCordOut[0],enuStationBernCordOut[1],enuStationBernCordOut[2]);
        System.out.println(sf); 

        // -  -

        // - EXAMPLE 2 -
        // Compute the coordinates in body reference frame from ecef
        System.out.println("Compute the coordinates in body reference frame...\n");
        tar_xyzb = ECEF.ecef2body(tar_xyz, xyzOb, ijkb);

        // Print the coordinates in body reference frame
        System.out.println("Coordinates in body reference frame:");
        sf=String.format("xyzb[m]: [%.8f; %.8f; %.8f]",tar_xyzb[0],tar_xyzb[1],tar_xyzb[2]);  
        System.out.println(sf);

        // Roll back the coordinates. Compute the coordinates in ecef reference frame
        System.out.println("Roll back the coordinates. Compute the coordinates in ecef reference frame...\n");
        tar_xyz = BODY.body2ecef(tar_xyzb, xyzOb, ijkb);

        // Print the coordinates in ecef reference frame
        System.out.println("Coordinates in ecef reference frame:");
        sf=String.format("xyz[m]: [%.8f; %.8f; %.8f]",tar_xyz[0],tar_xyz[1],tar_xyz[2]);  
        System.out.println(sf);

        // -  -
    }
    
}

