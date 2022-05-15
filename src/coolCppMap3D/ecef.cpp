/*
 * ecef.cpp
 *
 *  Created on: 24 abr 2022
 *      Author: MiguelRBF
 */

#include "ecef.h"

#include <cstdio>
#include <cmath>
#include <stdlib.h>

using namespace std;

void ecef2lla(long double xyz[], Ellipsoid ell, bool deg, long double lla[]){

	/*
	This function was created to change between ECEF coordinate system to
    geodetic of specified ellipsoid coordinate system
    (longitude, latitude, height).

    Equations taken from:
    http://wiki.gis.com/wiki/index.php/Geodetic_system

    Parameters
    ----------
    xyz={x, y, z}
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
    lla={lat, lon, alt}
    lat
        target geodetic latitude
    lon
        target geodetic longitude
    alt
        target altitude above geodetic ellipsoid (meters)
	 */

	// Define x, y z coordinates
	long double x=xyz[0], y=xyz[1], z=xyz[2];

	// Define intermediate parameters
	long double r2, r, E2, F, G, c, s, P, Q, ro, tmp, U, V, zo;

	r2 = pow(x,2) + pow(y,2);
	r = sqrt(r2);
	E2 = pow(ell.a,2) - pow(ell.b,2);
	F = 54*pow(ell.b,2)*pow(z,2);
	G = r2 + (1-ell.e2)*pow(z,2) - ell.e2*E2;
	c = (ell.e2*ell.e2*F*r2)/(G*G*G);
	s = pow( 1 + c + sqrt(c*c + 2*c), 1.0/3.0);
	P = F/(3*pow(s+1.0/s+1, 2)*G*G);
	Q = sqrt(1+2*ell.e2*ell.e2*P);
	ro = -(ell.e2*P*r)/(1+Q) + sqrt((ell.a*ell.a/2)*(1+1.0/Q) - ((1-ell.e2)*P*pow(z,2))/(Q*(1+Q)) - P*r2/2);
	tmp = pow(r - ell.e2*ro, 2);
	U = sqrt( tmp + z*z );
	V = sqrt( tmp + (1-ell.e2)*z*z );
	zo = (ell.b*ell.b*z)/(ell.a*V);

	// Now get the final coordinates: longitude, latitude and altitude
	lla[0] = atan((z+ell.ep2*zo)/r);
	lla[1] = atan2(y, x);
	lla[2] = U*(1 - ell.b*ell.b/(ell.a*V));

	// If degrees is wanted as output
	if (deg){
		// Convert the units of longitude and latitude from radians to degrees
		lla[0] = lla[0]*180.0/M_PI;
		lla[1] = lla[1]*180.0/M_PI;
	}
}

void ecef2enu_ecefRef(long double refXYZ[], long double xyz[], Ellipsoid ell, long double enu[]){
	/*
	This function convert ECEF coordinates to local east, north, up coordinates (ENU).

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
    enu={e, n, u}
    e
        target east ENU coordinate (meters)
    n
        target north ENU coordinate (meters)
    u
        target up ENU coordinate (meters)
	*/

	// Define reference x, y, z
	long double refX=refXYZ[0], refY=refXYZ[1], refZ=refXYZ[2];

	// Define target x, y, z
	long double x=xyz[0], y=xyz[1], z=xyz[2];

	// Define intermediate parameters
	long double refLLA[]={0, 0, 0};

	// First find reference location in latitude, longitude and height coordinates (radians)
    ecef2lla(refXYZ, ell, false, refLLA);

	// Get reference latitude, longitude coordinates
	long double refLat=refLLA[0], refLon=refLLA[1];

	//Compute ENU coordinates
	enu[0] = -sin(refLon)*(x-refX) + cos(refLon)*(y-refY);
	enu[1] = -sin(refLat)*cos(refLon)*(x-refX) - sin(refLat)*sin(refLon)*(y-refY) + cos(refLat)*(z-refZ);
	enu[2] = cos(refLat)*cos(refLon)*(x-refX) + cos(refLat)*sin(refLon)*(y-refY) + sin(refLat)*(z-refZ);

}

void ecef2enu_llaRef(long double refLLA[], long double xyz[], Ellipsoid ell, bool deg, long double enu[]){
	/*
	This function convert ECEF coordinates to local east, north, up coordinates.

    A reference point in geodetic coordinate system
    (latitude, longitude, height - refLat, refLong, refH)
    must be given. All distances are in metres.

    Equations taken from:
    http://wiki.gis.com/wiki/index.php/Geodetic_system

    Parameters
    ----------
    refLLA={refLat, refLon, refAlt}
    refLat
        reference geodetic latitude
    refLon
        reference geodetic longitude
    refAlt
        reference altitude above geodetic ellipsoid (meters)
    xyz={x, y, z}
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
    enu={e, n, u}
    e
        target east ENU coordinate (meters)
    n
        target north ENU coordinate (meters)
    u
        target up ENU coordinate (meters)
	*/

	// Define reference latitude, longitude coordinates
	long double refLat=refLLA[0], refLon=refLLA[1];

	// Define target x, y, z
	long double x=xyz[0], y=xyz[1], z=xyz[2];

	// Define intermediate parameters
	long double refXYZ[]={0,0,0};

	// First find reference location in ecef coordinates (x, y, z)
    lla2ecef(refLLA, ell, deg, refXYZ);

    //If the reference coordinates are given in degrees
    if (deg){
    	// Convert the reference latitude and longitude into radians
    	refLat = refLat*M_PI/180.0;
    	refLon = refLon*M_PI/180.0;
    }

	// Get reference ecef coordinates
	long double refX=refXYZ[0], refY=refXYZ[1], refZ=refXYZ[2];

	//Compute ENU coordinates
	enu[0] = -sin(refLon)*(x-refX) + cos(refLon)*(y-refY);
	enu[1] = -sin(refLat)*cos(refLon)*(x-refX) - sin(refLat)*sin(refLon)*(y-refY) + cos(refLat)*(z-refZ);
	enu[2] = cos(refLat)*cos(refLon)*(x-refX) + cos(refLat)*sin(refLon)*(y-refY) + sin(refLat)*(z-refZ);

}


void ecef2body(long double xyz[3], long double xyzOb[3], long double ijkb[3][3], long double xyzb[3]){
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

	Ob_P = inverse(R[θ]) * (Oecef_P-Oecef_Ob) = Rinv * diff_OeP_OeOb = Rinv * (xyz - xyzOb)
	 */

	// Define inverse(R[θ])
	long double Rinv[3][3] = {{ijkb[0][0], ijkb[1][0], ijkb[2][0]},
							 {ijkb[0][1], ijkb[1][1], ijkb[2][1]},
							 {ijkb[0][2], ijkb[1][2], ijkb[2][2]}};

	//  Get the difference between OeP (P coordinates in ecef reference) and
	// OeOb (vector from ecef origin to body origin).
	long double diff_OeP_OeOb[3];
	diff_OeP_OeOb[0] = xyz[0] - xyzOb[0];
	diff_OeP_OeOb[1] = xyz[1] - xyzOb[1];
	diff_OeP_OeOb[2] = xyz[2] - xyzOb[2];

	// Get the final coordinates in body reference
	multiplyMatVec(Rinv, diff_OeP_OeOb, xyzb);

}
