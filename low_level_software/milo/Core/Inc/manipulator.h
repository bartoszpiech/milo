/*
 * manipulator.h
 *
 *  Created on: 29 maj 2021
 *      Author: barti
 */

#ifndef INC_MANIPULATOR_H_
#define INC_MANIPULATOR_H_

#include "servo.h"
#include <stdio.h>

typedef struct {
	float x, y, z;
	float q1, q2, q3;
	float len[2];
	servo_t ft[3];
} manipulator_t;

void
manipulator_init(manipulator_t *m, float arm_len1, float arm_len2);

void
manipulator_update(manipulator_t *m);

void
manipulator_solve_fk(manipulator_t *m);

void
manipulator_solve_ik(manipulator_t *m);

#endif /* INC_MANIPULATOR_H_ */
