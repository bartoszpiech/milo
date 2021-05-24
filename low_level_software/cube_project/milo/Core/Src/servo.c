/*
 * servo.c
 *
 *  Created on: Mar 13, 2021
 *      Author: barti
 */

#include "servo.h"

void
servo_init(servo_t* servo,
		TIM_HandleTypeDef htm,
		uint8_t tch,
		uint16_t a,
		uint16_t amin,
		uint16_t amax,
		uint16_t pmin,
		uint16_t pmax) {
	servo->htim = htm;
	servo->tim_channel = tch;
	servo->angle = a;
	servo->angle_min = amin;
	servo->angle_max = amax;
	servo->pwm_min = pmin;
	servo->pwm_max = pmax;

	//servo_set(servo, a, 0);
}

uint16_t
servo_step(servo_t servo) {
	return ((1000 * (servo.pwm_max - servo.pwm_min)) / (servo.angle_max - servo.angle_min));
}

void
servo_set(servo_t* servo, uint16_t angle, uint8_t mode) {
	uint16_t val;
	servo->angle = angle;
	if (angle > servo->angle_max) {
		angle = servo->angle_max;
	} else if (angle < servo->angle_min) {
		angle = servo->angle_min;
	}
	if (mode) {
		val = servo->pwm_min + ((angle - servo->angle_min) * servo_step(*servo)) / 1000;
	} else {
		val = servo->pwm_max - ((angle - servo->angle_min) * servo_step(*servo)) / 1000;
	}
	__HAL_TIM_SET_COMPARE(&servo->htim, servo->tim_channel, val);
}

void
servo_print(servo_t servo) {
	printf("angle = %d\nangle_min = %d\nangle_max = %d\npwm_min = %d\npwm_max = %d\n", servo.angle, servo.angle_min, servo.angle_max, servo.pwm_min, servo.pwm_max);
}
