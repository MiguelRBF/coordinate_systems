/*
 * enu.cpp
 *
 *  Created on: 24 abr 2022
 *      Author: MiguelRBF
 */

#include "ecef.h"

using namespace std;

void enu2ecef_ecefRef(double refXYZ[], double enu[], Ellipsoid ell, double xyz[]){
	/*

	This function convert local east, north, up coordinates (labeled e, n, u) to ECEF coordinates.

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
    enu={e, n, u}
    e
        target east ENU coordinate (meters)
    n
        target north ENU coordinate (meters)
    u
        target up ENU coordinate (meters)

    ell : Ellipsoid, optional
          reference ellipsoid

    Returns
    -------
    xyz={x, y, z}
    x
        target x ECEF coordinate (meters)
    y
        target y ECEF coordinate (meters)
    z
        target z ECEF coordinate (meters)

	*/

	// Define reference x, y, z
	double refX=refXYZ[0], refY=refXYZ[1], refZ=refXYZ[2];

	// Define target e, n, u
	double e=enu[0], n=enu[1], u=enu[2];

	// Define intermediate parameters
	double refLLA[]={0, 0, 0};

	// First find reference location in LLA coordinates
    ecef2lla(refXYZ, ell, false, refLLA);

	// Get reference latitude, longitude coordinates
	double refLat=refLLA[0], refLon=refLLA[1];

	// Compute ecef coordinates
	xyz[0] = -sin(refLon)*e - cos(refLon)*sin(refLat)*n + cos(refLon)*cos(refLat)*u + refX;
	xyz[1] = cos(refLon)*e - sin(refLon)*sin(refLat)*n + cos(refLat)*sin(refLon)*u + refY;
    xyz[2] = cos(refLat)*n + sin(refLat)*u + refZ;

}

void enu2ecef_llaRef(double refLLA[], double enu[], Ellipsoid ell, bool deg, double xyz[]){
	/*
	This function convert local east, north, up coordinates (labeled e, n, u)
    to ECEF coordinates.

    A reference point in geodetic coordinate system
    (latitude, longitude, height - refLat, refLong, refH)
    must be given. Longitude and latitude can be given in decimal degrees
    or radians (default decimal degrees). All distances are in metres.

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
    enu={e, n, u}
    e
        target east ENU coordinate (meters)
    n
        target north ENU coordinate (meters)
    u
        target up ENU coordinate (meters)

    ell : Ellipsoid
          reference ellipsoid
    deg : bool, optional
          degrees input/output  (False: radians in/out)

    Returns
    -------
    xyz={x, y, z}
    x
        target x ECEF coordinate (meters)
    y
        target y ECEF coordinate (meters)
    z
        target z ECEF coordinate (meters)

	*/

	// Define reference latitude, longitude coordinates
	double refLat=refLLA[0], refLon=refLLA[1];

	// Define target e, n, u
	double e=enu[0], n=enu[1], u=enu[2];

	// Define intermediate parameters
	double refXYZ[]={0,0,0};

	// First find reference location ecef coordinates (x, y, z)
    lla2ecef(refLLA, ell, true, refXYZ);

    //If the reference coordinates are given in degrees
    if (deg){
    	// Convert the reference latitude and longitude into radians
        refLat = refLat*M_PI/180.0;
        refLon = refLon*M_PI/180.0;
    }

	// Get reference ecef coordinates
	double refX=refXYZ[0], refY=refXYZ[1], refZ=refXYZ[2];

	// Compute ecef coordinates
	xyz[0] = -sin(refLon)*e - cos(refLon)*sin(refLat)*n + cos(refLon)*cos(refLat)*u + refX;
	xyz[1] = cos(refLon)*e - sin(refLon)*sin(refLat)*n + cos(refLat)*sin(refLon)*u + refY;
	xyz[2] = cos(refLat)*n + sin(refLat)*u + refZ;

}
