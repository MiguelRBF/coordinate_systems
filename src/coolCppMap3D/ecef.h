/*
 * ecef.h
 *
 *  Created on: 24 abr 2022
 *      Author: MiguelRBF
 */

#ifndef ECEF_H
#define ECEF_H

// Include ellipsoid .h were is defined Ellipsoid class
#include "ellipsoid.h"

#include "lla.h"

void ecef2lla(long double xyz[], Ellipsoid ell, bool deg, long double lla[]);

void ecef2enu_ecefRef(long double refXYZ[], long double xyz[], Ellipsoid ell, long double enu[]);

void ecef2enu_llaRef(long double refLLA[], long double xyz[], Ellipsoid ell, bool deg, long double enu[]);

#endif /* ECEF_H */
