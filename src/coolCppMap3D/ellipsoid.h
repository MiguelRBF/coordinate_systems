/*
 * ellipsoid.h
 *
 *  Created on: 24 abr 2022
 *      Author: MiguelRBF
 */

#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include <string>
using namespace std;

class Ellipsoid
{

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
	public:

		Ellipsoid(string);

		// Create ellipsoid defining parameters
		long double a;
		long double f;
		// Create the ellipsoid derived geometric constants
		long double b;
		long double e2;
		long double ep2;


};

#endif /* ELLIPSOID_H */
