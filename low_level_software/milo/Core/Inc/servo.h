/*
 * servo.h
 *
 *  Created on: Mar 13, 2021
 *      Author: barti
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <stdio.h>
#include <stdint.h>
#include "tim.h"

/*
 * servo struct, holds information about servo and it's parameters
 */
typedef struct {
	TIM_HandleTypeDef htim;
	uint8_t tim_channel;
	uint16_t angle;
	uint16_t angle_min;
	uint16_t angle_max;
	uint16_t pwm_min;
	uint16_t pwm_max;
} servo_t;

void
servo_init(servo_t* servo,
		TIM_HandleTypeDef htm,
		uint8_t tch,
		uint16_t a,
		uint16_t amin,
		uint16_t amax,
		uint16_t pmin,
		uint16_t pmax);

uint16_t
servo_step(servo_t servo);

void
servo_set(servo_t* servo, uint16_t angle, uint8_t mode);

void
servo_print(servo_t servo);


#endif /* SERVO_H_ */
