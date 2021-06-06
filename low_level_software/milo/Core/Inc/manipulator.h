/*
 * manipulator.h
 *
 *  Created on: 29 maj 2021
 *      Author: barti
 */

#ifndef INC_MANIPULATOR_H_
#define INC_MANIPULATOR_H_

#include "servo.h"
#include "vector.h"
#include "tim.h"

typedef struct {
	// redundant
	vector_t origin;
	// redundant
	vector_t effector;
	vector_t j1[2];
	vector_t j2[2];

	double q[4];
	double len[2];
	double total_len;
	double error;

	servo_t servo[4];
} manipulator_t;

void
manipulator_init(manipulator_t *m);

void
manipulator_print(manipulator_t m);

void
manipulator_fk(manipulator_t *m);
void
manipulator_backward(manipulator_t *m, int depth, double x, double y, double z);

void
manipulator_forward(manipulator_t *m, int depth, double x, double y, double z);

void
manipulator_calculate_angles(manipulator_t *m);

void
manipulator_update(manipulator_t *m);

#endif /* INC_MANIPULATOR_H_ */
