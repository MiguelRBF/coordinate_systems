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

int main(){

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
	ecef2lla(xyz, ell_wgs84, lla, degrees);

	// Print output
	printf("Bern coordinates from xyz\n");
	printf("[l,l,a] = [%.12Lf,%.12Lf,%.12Lf]\n",lla[0],lla[1],lla[2]);

	// Get the x, y z coordinates
	lla2ecef(lla, ell_wgs84, xyz, degrees);

	// Print output
	printf("Bern coordinates from lla\n");
	printf("[x,y,z] = [%.12Lf,%.12Lf,%.12Lf]\n\n",xyz[0],xyz[1],xyz[2]);

	// Supose a reference GNSS station in Bern with and ENU error of:
    // E=1.0m , N=0.798654m and U=1.6543m
	long double  enu[] = {1.0,0.798654,1.6543};
    // Use as reference Bern position
	long double refXYZ[] = {4325481.828902193,565424.2388267403,4638228.339585699};
	long double refLLA[] = {46.9480900,7.4474400,549};

	// Get the x, y z coordinates
	enu2ecef_ecefRef(refXYZ, enu, ell_wgs84, xyz);

	// Print output
	printf("Bern coordinates from enu: xyz reference\n");
	printf("[x,y,z] = [%.12Lf,%.12Lf,%.12Lf]\n",xyz[0],xyz[1],xyz[2]);

	// Get the x, y z coordinates
	enu2ecef_llaRef(refLLA, enu, ell_wgs84, xyz, degrees);

	// Print output
	printf("Bern coordinates from enu: lla reference\n");
	printf("[x,y,z] = [%.12Lf,%.12Lf,%.12Lf]\n",xyz[0],xyz[1],xyz[2]);

    return 0;
}
