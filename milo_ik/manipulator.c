#include "manipulator.h"

void
manipulator_init(manipulator_t *m) {
	vector_init_d(&m->origin, 0, 0, 0);

	m->q[0] = 0;
	m->q[1] = 45.0;
	m->q[2] = 45.0;

	m->len[0] = 40.0;
	m->len[1] = 30.0;
	m->total_len = m->len[0] + m->len[1];
	m->error = 0.1;

	vector_init_v(&m->j1[0], m->origin);
	vector_init_d(&m->j1[1],
				m->len[0] * cos(m->q[1]) * cos(m->q[0]),
				m->len[0] * sin(m->q[1]),
				m->len[0] * cos(m->q[1]) * sin(m->q[0]));
	vector_init_v(&m->j2[0], m->j1[1]);
	vector_init_d(&m->j2[1],
				(m->len[0] * cos(m->q[1]) + m->len[1] * cos(m->q[1] + m->q[2])) * cos(m->q[0]),
				m->len[0] * sin(m->q[1]) + m->len[1] * sin(m->q[1] + m->q[2]),
				(m->len[0] * cos(m->q[1]) + m->len[1] * cos(m->q[1] + m->q[2])) * sin(m->q[0]));
	vector_init_v(&m->effector, m->j2[1]);

	servo_init(&m->ft[0], htim15, TIM_CHANNEL_1, 0, 0, 1800, 500, 2500);
	servo_init(&m->ft[1], htim16, TIM_CHANNEL_1, 0, 0, 1800, 500, 2500);
	servo_init(&m->ft[2], htim17, TIM_CHANNEL_1, 0, 0, 1800, 500, 2500);
}

void
manipulator_print(manipulator_t m) {
	printf("{\n");
	printf("q1 =\t%lfdeg\n", m.q[0] * 180 / M_PI);
	printf("q2 =\t%lfdeg\n", m.q[1] * 180 / M_PI);
	printf("q3 =\t%lfdeg\n", m.q[2] * 180 / M_PI);
	printf("m.j1[0] =\t");
	vector_print(m.j1[0]);
	printf("\nm.j1[1] =\t");
	vector_print(m.j1[1]);

	printf("\n\nm.j2[0] =\t");
	vector_print(m.j2[0]);
	printf("\nm.j2[1] =\t");
	vector_print(m.j2[1]);
	printf("\n}\n");
}

// function declaration
void
manipulator_forward(manipulator_t *m, int depth, double x, double y, double z);

void
manipulator_backward(manipulator_t *m, int depth, double x, double y, double z) {
	vector_init_d(&m->j2[1], x, y, z);
	if (vector_mag(m->j2[1]) > m->total_len) {
		printf("za daleko\n");
		return;
	}
	vector_t tmp;
	// substract end of the joint from it's beginning
	vector_sub(&tmp, m->j2[0], m->j2[1]);
	vector_normalize(&tmp);
	// multiplying * length of a joint
	vector_mult(&tmp, m->len[1]);
	// adding end coords
	vector_add(&tmp, tmp, m->j2[1]);
	vector_init_v(&m->j2[0], tmp);

	// set end of first joint and repeat the process
	vector_init_v(&m->j1[1], m->j2[0]);
	vector_sub(&tmp, m->j1[0], m->j1[1]);
	vector_normalize(&tmp);
	vector_mult(&tmp, m->len[0]);
	vector_add(&tmp, tmp, m->j1[1]);
	vector_init_v(&m->j1[0], tmp);

	manipulator_forward(m, depth, x, y, z);
}

void
manipulator_forward(manipulator_t *m, int depth, double x, double y, double z) {
	depth--;
	//printf("forward\n");
	vector_init_v(&m->j1[0], m->origin);
	vector_t tmp;
	vector_sub(&tmp, m->j1[1], m->j1[0]);
	vector_normalize(&tmp);
	vector_mult(&tmp, m->len[0]);
	vector_init_v(&m->j1[1], tmp);
	vector_init_v(&m->j2[0], m->j1[1]);
	//vector_print(m->j1[1]);

	vector_sub(&tmp, m->j2[1], m->j2[0]);
	vector_normalize(&tmp);
	vector_mult(&tmp, m->len[1]);
	vector_add(&tmp, tmp, m->j2[0]);
	vector_init_v(&m->j2[1], tmp);
	
	// error check
	vector_init_d(&tmp, x, y, z);
	vector_sub(&tmp, tmp, m->j2[1]);
	if (fabs(vector_mag(tmp)) > m->error || depth >= 0) {
		manipulator_backward(m, depth, x, y, z);
	}
}

void
manipulator_calculate_angles(manipulator_t *m) {
	vector_t x_tmp;
	vector_t y_tmp;
	vector_t x_axis;

	// set temporary vector to j1b on x plane to calculate q1 and q2
	vector_init_d(&x_tmp, m->j1[1].x, 0, m->j1[1].z);
	// set temporary vector to j2b
	vector_init_v(&y_tmp, m->j2[1]);
	// set x axis vector to compute q1
	vector_init_d(&x_axis, 1, 0, 0);
	// move our tmp vector to origin
	vector_sub(&y_tmp, y_tmp, m->j2[0]);
	m->q[0] = vector_angle(x_tmp, x_axis);
	m->q[1] = vector_angle(m->j1[1], x_tmp);
	m->q[2] = vector_angle(y_tmp, x_tmp) - m->q[1];
	manipulator_print(*m);
}

void
manipulator_update(manipulator_t *m) {
	manipulator_backwards(m, m->effector.x, m->effector.y, m->effector.z);
	manipulator_calculate_angles(m);
	servo_set(&m->ft[0], (int)m->q1 * 10, 0);
	servo_set(&m->ft[1], (int)m->q2 * 10, 0);
	servo_set(&m->ft[2], (int)m->q3 * 10, 0);
}
