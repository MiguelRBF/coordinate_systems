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

#include "multiplyMatVec.h"

void ecef2lla(double xyz[], Ellipsoid ell, bool deg, double lla[]);

void ecef2enu_ecefRef(double refXYZ[], double xyz[], Ellipsoid ell, double enu[]);

void ecef2enu_llaRef(double refLLA[], double xyz[], Ellipsoid ell, bool deg, double enu[]);

void ecef2body(double xyz[3], double xyzOb[3], double ijkb[3][3], double xyzb[3]);

#endif /* ECEF_H */
