/*
 * body.h
 *
 *  Created on: 24 abr 2022
 *      Author: MiguelRBF
 */

#ifndef BODY_H
#define BODY_H

#include "multiplyMatVec.h"

void body2ecef(double xyz[3], double xyzOb[3], double ijkb[3][3], double xyzb[3]);

#endif /* BODY_H */
