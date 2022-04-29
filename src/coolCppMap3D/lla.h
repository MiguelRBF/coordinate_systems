/*
 * lla.h
 *
 *  Created on: 24 abr 2022
 *      Author: MiguelRBF
 */

#ifndef LLA_H
#define LLA_H

// Include ellipsoid .h were is defined Ellipsoid class
#include "ellipsoid.h"

void lla2ecef(long double lla[], Ellipsoid ell, bool deg, long double xyz[]);

#endif /* LLA_H */
