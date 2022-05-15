//--------------------------------------------
// Module name:      MatVec.java
// Created by:       MiguelRBF
//--------------------------------------------

// Package definition
package MatVec;

public class MatVec {

    // --- Class attributes ---
    
    // ---  ---

    // Class constructor
    public MatVec(){   
    }

    // Define multiplyMatVec method
    static public double[] multiplyMatVec(double[][] mat, double[] vec){

        /*
    	This function was created to manage the multiplication
    	between 1 matrix (3x3) and a vector (3).

    	Returns a vector res (3).
    	*/

    	// Set to zero all res components
        // Define output method parameters
        double[] res = new double[]{0.0, 0.0, 0.0};

        int i, j;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
            	res[i] = res[i] + mat[i][j] * vec[j];
            }
        }

        // Return output coordinates
        return res;
    }
}
