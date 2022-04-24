/*
 * lla.cpp
 *
 *  Created on: 24 abr 2022
 *      Author: MiguelRBF
 */

#include "lla.h"

#include <cmath>
#include <stdlib.h>

using namespace std;

void lla2ecef(long double lla[], Ellipsoid ell, long double xyz[], bool deg){

	/*
	Convert lat, long, altitude in geodetic of specified ellipsoid
    to ECEF X,Y,Z. Longitude and latitude can be given in decimal
    degrees or radians. Altitude must be given in meters.

    Equations taken from:
    http://wiki.gis.com/wiki/index.php/Geodetic_system

    Parameters
    ----------
    lla={lat, lon, alt}
    lat
        target geodetic latitude
    lon
        target geodetic longitude
    alt
        target altitude above geodetic ellipsoid (meters)

    ell : Ellipsoid
          reference ellipsoid
    deg : bool
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


	// Define latitude, longitude altitude coordinates
	long double lat=lla[0], lon=lla[1], alt=lla[2];

	// Define intermediate parameters
	long double chi;

	// If degrees is wanted as input
	if(deg){
		// Convert longitude-latitude units from degrees to radians
		lat = lat*M_PI/180.0;
		lon = lon*M_PI/180.0;
	}

	// Compute chi parameter
    chi = sqrt(1-ell.e2*pow(sin(lat),2));

	// Compute x, y and z coordinates
    xyz[0] = (ell.a/chi +alt)*cos(lat)*cos(lon);
    xyz[1] = (ell.a/chi +alt)*cos(lat)*sin(lon);
    xyz[2] = (ell.a*(1-ell.e2)/chi + alt)*sin(lat);
}
