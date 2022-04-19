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
#include <stdlib.h>

using namespace std;

class Ellipsoid{	// The class

	/*
	Class adapted from geospace-code
    generate reference ellipsoid parameters
    https://en.wikibooks.org/wiki/PROJ.4#Spheroid
    https://nssdc.gsfc.nasa.gov/planetary/factsheet/index.html
    as everywhere else in this program, distance units are METERS

    Ellipsoid defining parameters:
    a = semimajor_axis
    f = (first) flattening

    Ellipsoid derived geometric constants:
    b = semiminor_axis = a·(1-f)
    e2 = (first) eccentricity squared = (2-f)·f
    ep2 = second eccentricity squared = f·(2-f)/(1-f)^2
	 */

	public:							// Access specifier

		// Create ellipsoid defining parameters
		long double a;
		long double f;
		// Create the ellipsoid derived geometric constants
		long double b;
		long double e2;
		long double ep2;

		Ellipsoid(string mod){		// Constructor with parameters
			string model = mod;

			// WGS84 defining parameters
			if (model == "wgs84"){
				a = 6378137.0;
				f = 1/298.257223563;
				// WGS84 derived parameter
				b = a*(1-f);

			// WGS72 defining parameters
			}else if (model == "wgs72"){

				a = 6378135.0;
				b = 6356750.52001609;

			// GRS80 defining parameters
			}else if (model == "grs80"){

				a = 6378137.0;
				b = 6356752.31414036;

			// Mars defining parameters
			}else if (model == "mars"){
				// https://tharsis.gsfc.nasa.gov/geodesy.html
				a = 3396900.0;
				b = 3376097.80585952;

			// Moon defining parameters
			}else if (model == "moon"){
				a = 1738000.0;
				b = 1738000.0;

			// Venus defining parameters
			}else if (model == "venus"){
				a = 6051000.0;
				b = 6051000.0;

			// Jupiter defining parameters
			}else if (model == "jupiter"){
				a = 71492000.0;
				b = 66770054.3475922;

			// Pluto defining parameters
			}else if (model == "pluto"){
				a = 1187000.0;
				b = 1187000.0;
			}
			// If the parameter is not any one of the defined...
			else {
				cout << "Invalid model\n";
				exit(0);
			}

			// In wgs84 the flattening is a defining parameter. In the other ellipsoids
			// the semiminor_axis is the second defining parameter.
			if (model != "wgs84"){
				f = (a - b) / a;
			}

			// Create the rest of the ellipsoid derived geometric constants
			e2 = 2*f - f*f;
			ep2 = f*(2-f)/pow(1-f,2);
		}

};

void ecef2lla(long double xyz[], Ellipsoid ell, long double lla[], bool deg){

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
	c=(ell.e2*ell.e2*F*r2)/(G*G*G);
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

void ecef2enu_ecefRef(long double refXYZ[], long double xyz[], Ellipsoid ell, long double enu[]){
	/*
	This function convert ECEF coordinates to local east, north, up coordinates (ENU).

    A reference point in ECEF coordinates (x, y, z - refX, refY, refZ)
    must be given. All distances are in meters.

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
    ecef2lla(refXYZ, ell, refLLA, false);

	// Get reference latitude, longitude altitude coordinates
	long double refLat=refLLA[0], refLon=refLLA[1], refAlt=refLLA[2];

	//Compute ENU coordinates
	enu[0] = -sin(refLon)*(x-refX) + cos(refLon)*(y-refY);
	enu[1] = -sin(refLat)*cos(refLon)*(x-refX) - sin(refLat)*sin(refLon)*(y-refY) + cos(refLat)*(z-refZ);
	enu[2] = cos(refLat)*cos(refLon)*(x-refX) + cos(refLat)*sin(refLon)*(y-refY) + sin(refLat)*(z-refZ);

}

void ecef2enu_llaRef(long double refLLA[], long double xyz[], Ellipsoid ell, long double enu[], bool deg){
	/*
	This function convert ECEF coordinates to local east, north, up coordinates.

    A reference point in geodetic coordinate system
    (latitude, longitude, height - refLat, refLong, refH)
    must be given. All distances are in metres.

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

    ell : Ellipsoid
          reference ellipsoid
    deg : bool, optional
          degrees input/output  (False: radians in/out)

    Returns
    -------
    e
        target east ENU coordinate (meters)
    n
        target north ENU coordinate (meters)
    u
        target up ENU coordinate (meters)
	*/

	// Define reference latitude, longitude altitude coordinates
	long double refLat=refLLA[0], refLon=refLLA[1], refAlt=refLLA[2];

	// Define target x, y, z
	long double x=xyz[0], y=xyz[1], z=xyz[2];

	// Define intermediate parameters
	long double refXYZ[]={0,0,0};

	// First find reference location ecef coordinates (x, y, z)
    lla2ecef(refLLA, ell, refXYZ, false)

	// Get reference ecef coordinates
	long double refX=refXYZ[0], refY=refXYZ[1], refZ=refXYZ[2];

	//Compute ENU coordinates
	enu[0] = -sin(refLon)*(x-refX) + cos(refLon)*(y-refY);
	enu[1] = -sin(refLat)*cos(refLon)*(x-refX) - sin(refLat)*sin(refLon)*(y-refY) + cos(refLat)*(z-refZ);
	enu[2] = cos(refLat)*cos(refLon)*(x-refX) + cos(refLat)*sin(refLon)*(y-refY) + sin(refLat)*(z-refZ);

}

int main(){

	// Bern coordinates (latitude, longitude, altitude)
	long double xyz[]={4325481.828902193,565424.2388267403,4638228.339585699};

	// Initiate latitude, longitude altitude coordinates
	long double lla[]= {0,0,0};

	// Create ellipsoid wgs84 object
	Ellipsoid ell_wgs84("wgs84");

	// Define boolean variable to make the function to output degrees
	bool degrees = true;

	// Get the latitude, longitude and altitude coordinates
	ecef2lla(xyz, ell_wgs84, lla, degrees);

	// Print output
	cout << "lla = [ ";
	for (int i = 0; i < 2; ++i) {
	    cout << std::setprecision(16) << lla[i] << ", ";
	    cout << std::setprecision(16) << lla[2];
	}
	cout << "]" << endl;

	// Get the x, y z coordinates
	lla2ecef(lla, ell_wgs84, xyz, degrees);

	// Print output
		cout << "xyz = [ ";
		for (int i = 0; i < 2; ++i) {
		    cout << std::setprecision(16) << xyz[i] << ", ";
		}
		cout << std::setprecision(16) << xyz[2];
		cout << "]" << endl;

    return 0;
}
