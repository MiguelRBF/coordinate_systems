/*
 * ecef.h
 *
 *  Created on: 24 abr 2022
 *      Author: MiguelRBF
 */

#ifndef ENU_H
#define ENU_H

// Include ellipsoid .h were is defined Ellipsoid class
#include "ellipsoid.h"

#include "lla.h"
#include "ecef.h"

void enu2ecef_ecefRef(long double refXYZ[], long double enu[], Ellipsoid ell, long double xyz[]);

void enu2ecef_llaRef(long double refLLA[], long double enu[], Ellipsoid ell, long double xyz[], bool deg);

#endif /* ENU_H */
