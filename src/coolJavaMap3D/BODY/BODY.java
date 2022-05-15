//--------------------------------------------
// Module name:      BODY.java
// Created by:       MiguelRBF
//--------------------------------------------

// Package definition
package BODY;

// Import used packages
import MatVec.MatVec;

public class BODY {

    // --- Class attributes ---
    
    // ---  ---

    // Class constructor
    public BODY(){   
    }

    // Define multiplyMatVec method
    static public double[] body2ecef(double[] xyzb, double[] xyzOb, double[][] ijkb){

        /*
	    This function was created to change between ecef
	    to Body coordinate system.

	    Parameters
	    ----------
	    xb = xyzb[0]
        	target x Body coordinate (meters)
	    yb = xyzb[1]
        	target y Body coordinate (meters)
	    zb = xyzb[2]
        	target z Body coordinate (meters)

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

	    x = xyz[0]
        	target x ecef coordinate (meters)
	    y = xyz[1]
        	target y ecef coordinate (meters)
	    z = xyz[1]
        	target z ecef coordinate (meters)

	    O1_P = O1_O2 + R[θ] * O2_P
	     */
        
        // Define output method parameters
        double[] xyz = new double[]{0.0, 0.0, 0.0};

         // Define R[θ]
	    double[][] R = {{ijkb[0][0], ijkb[0][1], ijkb[0][2]},
                        {ijkb[1][0], ijkb[1][1], ijkb[1][2]},
                        {ijkb[2][0], ijkb[2][1], ijkb[2][2]}};

        // Initialize intermediate variables
        double[] rotCoor = new double[]{0.0, 0.0, 0.0};

        // Get the coordinates after rotation
        rotCoor = MatVec.multiplyMatVec(R, xyzb);

        // Get the final coordinates in ecef reference
        xyz[0] = xyzOb[0] + rotCoor[0];
        xyz[1] = xyzOb[1] + rotCoor[1];
        xyz[2] = xyzOb[2] + rotCoor[2];

        // Return output coordinates
        return xyz;
    }
}
