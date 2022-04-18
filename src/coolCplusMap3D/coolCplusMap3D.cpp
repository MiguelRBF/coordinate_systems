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


			if (model == "wgs84"){
				a = 6378137.0;
				f = 1/298.257223563;
				b = a*(1-f);

			}else if (model == "wgs72"){

				a = 6378135.0;
				b = 6356750.52001609;
				f = (a - b) / a;

			} else {
				cout << "Invalid model\n";
				exit(0);
			}

			e2 = 2*f - f*f;
			ep2 = f*(2-f)/pow(1-f,2);
		}

};

void ecef2llh(long double xyz[], Ellipsoid ell, long double lla[], bool deg){

	/*
	This function was created to change between ECEF coordinate system to
    geodetic of specified ellipsoid coordinate system
    (longitude, latitude, height).

    Equations taken from:
    http://wiki.gis.com/wiki/index.php/Geodetic_system

    Parameters
    ----------
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
    lat
        target geodetic latitude
    lon
        target geodetic longitude
    alt
        target altitude above geodetic ellipsoid (meters)
	 */

	// Define x, y z coordinates
	long double x=xyz[0], y=xyz[1], z=xyz[2];
	// Define ellipse parameters
	long double a=ell.a, b=ell.b, e2=ell.e2, ep2=ell.ep2;

	// Define intermediate parameters
	long double r2, r, E2, F, G, c, s, P, Q, ro, tmp, U, V, zo;

	r2 = pow(x,2) + pow(y,2);
	r = sqrt(r2);
	E2 = pow(a,2) - pow(b,2);
	F = 54*pow(b,2)*pow(z,2);
	G = r2 + (1-e2)*pow(z,2) - e2*E2;
	c=(e2*e2*F*r2)/(G*G*G);
	s = pow( 1 + c + sqrt(c*c + 2*c), 1.0/3.0);
	P = F/(3*pow(s+1.0/s+1, 2)*G*G);
	Q = sqrt(1+2*e2*e2*P);
	ro = -(e2*P*r)/(1+Q) + sqrt((a*a/2)*(1+1.0/Q) - ((1-e2)*P*pow(z,2))/(Q*(1+Q)) - P*r2/2);
	tmp = pow(r - e2*ro, 2);
	U = sqrt( tmp + z*z );
	V = sqrt( tmp + (1-e2)*z*z );
	zo = (b*b*z)/(a*V);

	// Now get the final coordinates: longitude, latitude and altitude
	lla[0] = atan((z+ep2*zo)/r);
	lla[1] = atan2(y, x);
	lla[2] = U*(1 - b*b/(a*V));

	// If degrees is wanted as output
	if (deg){
		// Convert the units of longitude and latitude from radians to degrees
		lla[0] = lla[0]*180.0/M_PI;
		lla[1] = lla[1]*180.0/M_PI;
	}
}

void llh2ecef(long double lla[], Ellipsoid ell, long double xyz[], bool deg){

	/*
	Convert lat, long, height in geodetic of specified ellipsoid
    to ECEF X,Y,Z. Longitude and latitude can be given in decimal
    degrees or radians. Altitude must be given in meters.

    Equations taken from:
    http://wiki.gis.com/wiki/index.php/Geodetic_system

    Parameters
    ----------
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
    x
        target x ECEF coordinate (meters)
    y
        target y ECEF coordinate (meters)
    z
        target z ECEF coordinate (meters)
	 */

	// Define latitude, longitude altitude coordinates
	long double lat=lla[0], lon=lla[1], alt=lla[2];
	// Define ellipse parameters
	long double a=ell.a, e2=ell.e2;

	// Define intermediate parameters
	long double chi;

	// If degrees is wanted as input
	if(deg){
		// Convert longitude-latitude units from degrees to radians
		lat = lat*M_PI/180.0;
		lon = lon*M_PI/180.0;
	}

	// Compute chi parameter
    chi = sqrt(1-e2*pow(sin(lat),2));

	// Compute x, y and z coordinates
    xyz[0] = (a/chi +alt)*cos(lat)*cos(lon);
    xyz[1] = (a/chi +alt)*cos(lat)*sin(lon);
    xyz[2] = (a*(1-ell.e2)/chi + alt)*sin(lat);
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
	ecef2llh(xyz, ell_wgs84, lla, degrees);

	// Print output
	cout << "lla = [ ";
	for (int i = 0; i < 2; ++i) {
	    cout << std::setprecision(16) << lla[i] << ", ";
	    cout << std::setprecision(16) << lla[2];
	}
	cout << "]" << endl;

	// Get the x, y z coordinates
	llh2ecef(lla, ell_wgs84, xyz, degrees);

	// Print output
		cout << "xyz = [ ";
		for (int i = 0; i < 2; ++i) {
		    cout << std::setprecision(16) << xyz[i] << ", ";
		}
		cout << std::setprecision(16) << xyz[2];
		cout << "]" << endl;

    return 0;
}
