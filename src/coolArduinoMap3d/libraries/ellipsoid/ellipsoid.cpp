/*
 * ellipsoid.cpp
 *
 *  Created on: 24 abr 2022
 *      Author: MiguelRBF
 */

#include "ellipsoid.h"

#include "Arduino.h"

using namespace std;

Ellipsoid::Ellipsoid(String _model)	// Constructor with parameters
{

	// WGS84 defining parameters
	if (_model == "wgs84"){
		a = 6378137.0;
		f = 1/298.257223563;
		// WGS84 derived parameter
		b = a*(1-f);

	// WGS72 defining parameters
	}else if (_model == "wgs72"){

		a = 6378135.0;
		b = 6356750.52001609;

	// GRS80 defining parameters
	}else if (_model == "grs80"){

		a = 6378137.0;
		b = 6356752.31414036;

	// Mars defining parameters
	}else if (_model == "mars"){
		// https://tharsis.gsfc.nasa.gov/geodesy.html
		a = 3396900.0;
		b = 3376097.80585952;

	// Moon defining parameters
	}else if (_model == "moon"){
		a = 1738000.0;
		b = 1738000.0;

	// Venus defining parameters
	}else if (_model == "venus"){
		a = 6051000.0;
		b = 6051000.0;

	// Jupiter defining parameters
	}else if (_model == "jupiter"){
		a = 71492000.0;
		b = 66770054.3475922;

	// Pluto defining parameters
	}else if (_model == "pluto"){
		a = 1187000.0;
		b = 1187000.0;
	}
	// If the parameter is not any one of the defined...
	else {
		//cout << "Invalid model\n";
		//exit(0);
	}

	// In wgs84 the flattening is a defining parameter. In the other ellipsoids
	// the semiminor_axis is the second defining parameter.
	if (_model != "wgs84"){
		f = (a - b) / a;
	}

	// Create the rest of the ellipsoid derived geometric constants
	e2 = 2*f - f*f;
	ep2 = f*(2-f)/pow(1-f,2);

}
