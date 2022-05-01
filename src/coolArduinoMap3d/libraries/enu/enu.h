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

void enu2ecef_ecefRef(double refXYZ[], double enu[], Ellipsoid ell, double xyz[]);

void enu2ecef_llaRef(double refLLA[], double enu[], Ellipsoid ell, bool deg, double xyz[]);

#endif /* ENU_H */
