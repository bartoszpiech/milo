/*
 * manipulator.c
 *
 *  Created on: 29 maj 2021
 *      Author: barti
 */


#include "manipulator.h"

void
manipulator_init(manipulator_t *m, float arm_len1, float arm_len2) {
	m->len[0] = arm_len1;
	m->len[1] = arm_len2;
	m->q1 = 0;
	m->q2 = 0;
	m->q3 = 0;
	manipulator_solve_fk(m);
	servo_init(&m->ft[0], htim15, TIM_CHANNEL_1, 0, 0, 1800, 500, 2500);
	servo_init(&m->ft[1], htim16, TIM_CHANNEL_1, 0, 0, 1800, 500, 2500);
	servo_init(&m->ft[2], htim17, TIM_CHANNEL_1, 0, 0, 1800, 500, 2500);
}

void
manipulator_update(manipulator_t *m) {
	manipulator_solve_ik(m);
	servo_set(&m->ft[0], (int)m->q1 * 10, 0);
	servo_set(&m->ft[1], (int)m->q2 * 10, 0);
	servo_set(&m->ft[2], (int)m->q3 * 10, 0);
}

// forward kinematics
void
manipulator_solve_fk(manipulator_t *m) {
	m->x = (m->len[0] * cos(m->q2) +
			m->len[1] * cos(m->q2 + m->q3)) * cos(m->q1);

	m->y = m->len[0] * sin(m->q2) + m->len[1] * sin(m->q2 + m->q3);


	m->z = (m->len[0] * cos(m->q2) +
			m->len[1] * cos(m->q2 + m->q3)) * sin(m->q1);
}


// inverse kinematics
void
manipulator_solve_ik(manipulator_t *m) {
	m->q3 = acos(
			(m->x * m->x + m->y * m->y + m->z * m->z -
			(m->len[0] * m->len[0]) - (m->len[1] * m->len[1])) /
			(2 * m->len[0] * m->len[1]));

	m->q2 = asin(
			(m->y * m->y - m->len[1] * m->len[1] * sin(m->q3) * sin(m->q3)) /
			(m->len[0] * m->len[0] + m->len[1] * m->len[1] *
			 cos(m->q3) * cos(m->q3) + 2 * m->len[0] * m->len[1] * cos(m->q3) -
			 m->len[1] * m->len[1] * sin(m->q3) * sin(m->q3)));

	m->q3 = acos(
			 x /
			(m->len[0] * cos(m->q2) + m->len[1] * cos(m->q2 + m->q3);
}
