//============================================================================
// Name        : coolCplusMap3D.cpp
// Author      : Miguel
// Version     :
// Copyright   : Your copyright notice
// Description : Ansi-style
//============================================================================

#include <iostream>
#include <iomanip> // std::setprecision
#include <cmath>
#include <string>

// Include standard input output functions
#include <stdio.h>

using namespace std;

#include "ellipsoid.h"
#include "ecef.h"
#include "lla.h"
#include "enu.h"
#include "body.h"

int main(){

	// --- EXAMPLE 1 ---

	printf("--- EXAMPLE 1 ---\n\n");

	// Bern coordinates (x, y, z)
	long double xyz[] = {4325481.828902193,565424.2388267403,4638228.339585699};

	// Initiate latitude, longitude altitude coordinates
	long double lla[] = {0,0,0};

	// Create ellipsoid wgs84 object
	Ellipsoid ell_wgs84("wgs84");

	// Define boolean variable to make the functions to input/output degrees
	bool degrees = true;

	// Print "Bern coordinates computations"
	printf("Bern coordinates computations\n");

	// Get the latitude, longitude and altitude coordinates
	ecef2lla(xyz, ell_wgs84, degrees, lla);

	// Print output
	printf("Bern coordinates from xyz\n");
	printf("[l,l,a] = [%.12Lf,%.12Lf,%.12Lf]\n",lla[0],lla[1],lla[2]);

	// Get the x, y z coordinates
	lla2ecef(lla, ell_wgs84, degrees, xyz);

	// Print output
	printf("Bern coordinates from lla\n");
	printf("[x,y,z] = [%.12Lf,%.12Lf,%.12Lf]\n\n",xyz[0],xyz[1],xyz[2]);

	// Supose a reference GNSS station in Bern with and ENU error of:
    // E=1.0m , N=0.798654m and U=1.6543m
	long double  enu[] = {1.0,0.798654,1.6543};
    // Use as reference Bern position
	long double refXYZ[] = {4325481.828902193,565424.2388267403,4638228.339585699};
	long double refLLA[] = {46.9480900,7.4474400,549};

	// Get the x, y z coordinates. ECEF reference
	enu2ecef_ecefRef(refXYZ, enu, ell_wgs84, xyz);

	// Print output
	printf("Bern xyz coordinates from enu: ecef reference\n");
	printf("[x,y,z] = [%.12Lf,%.12Lf,%.12Lf]\n",xyz[0],xyz[1],xyz[2]);

	// Get the x, y z coordinates. LLA reference
	enu2ecef_llaRef(refLLA, enu, ell_wgs84, degrees, xyz);

	// Print output
	printf("Bern xyz coordinates from enu: lla reference\n");
	printf("[x,y,z] = [%.12Lf,%.12Lf,%.12Lf]\n\n",xyz[0],xyz[1],xyz[2]);

	// Get the enu coordinates. ECEF reference
	ecef2enu_ecefRef(refXYZ, xyz, ell_wgs84, enu);

	// Print output
	printf("Bern enu coordinates from xyz: ecef reference\n");
	printf("[e,n,u] = [%.12Lf,%.12Lf,%.12Lf]\n",enu[0],enu[1],enu[2]);

	// Get the enu coordinates. ECEF reference
	ecef2enu_llaRef(refLLA, xyz, ell_wgs84, degrees, enu);

	// Print output
	printf("Bern enu coordinates from xyz: lla reference\n");
	printf("[e,n,u] = [%.12Lf,%.12Lf,%.12Lf]\n\n",enu[0],enu[1],enu[2]);

	// ---  ---

	// --- EXAMPLE 2 ---
	printf("--- EXAMPLE 2 ---\n\n");

	// Define the rotation matrix R[θ]=ijkb
	long double ijkb[3][3] = {{1., 0., 0.},
						{0., 1., 0.},
						{0., 0., 1.}};

	// Define the target ecef coordinates
	long double tar_xyz[3] = {26600000., 10., 0.};

	// define the body origin coordinates
	long double xyzOb[3] = {26600000., 0., 0.};

	// Initialize target body coordinates
	long double tar_xyzb[3] = {0, 0, 0};

	// Compute the coordinates in body reference frame
	ecef2body(tar_xyz, xyzOb, ijkb, tar_xyzb);

	printf("Body coordinates from ecef reference frame\n");
	printf("xyzb[x,y,z] = [%.12Lf,%.12Lf,%.12Lf]\n\n",tar_xyzb[0],tar_xyzb[1],tar_xyzb[2]);

	// Roll back the coordinates. Compute the coordinates in ecef reference frame
	body2ecef(tar_xyzb, xyzOb, ijkb, tar_xyz);

	printf("Ecef coordinates from body reference frame\n");
	printf("xyz[x,y,z] = [%.12Lf,%.12Lf,%.12Lf]\n\n",tar_xyz[0],tar_xyz[1],tar_xyz[2]);


	// ---  ---

    return 0;
}
