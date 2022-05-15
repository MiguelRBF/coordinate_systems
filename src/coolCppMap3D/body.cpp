/*
 * body.cpp
 *
 *  Created on: 15 may 2022
 *      Author: MiguelRBF
 */

#include "body.h"

#include <cstdio>
#include <cmath>
#include <stdlib.h>

using namespace std;

void body2ecef(long double xyzb[3], long double xyzOb[3], long double ijkb[3][3], long double xyz[3]){
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

	// Define R[θ]
	long double R[3][3] = {{ijkb[0][0], ijkb[0][1], ijkb[0][2]},
						   {ijkb[1][0], ijkb[1][1], ijkb[1][2]},
						   {ijkb[2][0], ijkb[2][1], ijkb[2][2]}};

	// Get the coordinates after rotation
	long double rotCoor[3];
	multiplyMatVec(R, xyzb, rotCoor);

	// Get the final coordinates in ecef reference
	xyz[0] = xyzOb[0] + rotCoor[0];
	xyz[1] = xyzOb[1] + rotCoor[1];
	xyz[2] = xyzOb[2] + rotCoor[2];

}
