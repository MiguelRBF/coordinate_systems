/*
 * ecef.cpp
 *
 *  Created on: 15 may 2022
 *      Author: MiguelRBF
 */

#include "multiplyMatVec.h"

#include <cstdio>
#include <cmath>
#include <stdlib.h>

using namespace std;

// --- Matrix multiplication function ---

void multiplyMatVec(long double mat[3][3], long double vec[3], long double res[3]){
	/*
	This function was created to manage the multiplication
	between 1 matrix (3x3) and a vector (3).

	Returns a vector res (3).
	*/

	// Set to zero all res components
	res[0] = 0;
	res[1] = 0;
	res[2] = 0;

    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
        	res[i] = res[i] + mat[i][j] * vec[j];
        }
    }
}


// ---  ---

