#include <stdio.h>
#include <math.h>

typedef struct {
	double x;
	double y;
	double z;
} vector_t;

void
vector_init_d(vector_t *v, double x, double y, double z) {
	v->x = x;
	v->y = y;
	v->z = z;
}

void
vector_init_v(vector_t *v, vector_t src) {
	v->x = src.x;
	v->y = src.y;
	v->z = src.z;
}

void
vector_print(vector_t v) {
	printf("[%lf, %lf, %lf]", v.x, v.y, v.z);
}

double
vector_mag(vector_t v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double
vector_dot(vector_t vec1, vector_t vec2) {
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

double
vector_angle(vector_t vec1, vector_t vec2) {
	return acos((vector_dot(vec1, vec2)) /
			(vector_mag(vec1) * vector_mag(vec2)));
}
void
vector_add(vector_t *v, vector_t vec1, vector_t vec2) {
	v->x = vec1.x + vec2.x;
	v->y = vec1.y + vec2.y;
	v->z = vec1.z + vec2.z;
}

void
vector_sub(vector_t *v, vector_t vec1, vector_t vec2) {
	v->x = vec1.x - vec2.x;
	v->y = vec1.y - vec2.y;
	v->z = vec1.z - vec2.z;
}

void
vector_mult(vector_t *v, double num) {
	v->x *= num;
	v->y *= num;
	v->z *= num;
}

void
vector_normalize(vector_t *v) {
	double div = vector_mag(*v);
	v->x = v->x / div;
	v->y = v->y / div;
	v->z = v->z / div;
}

typedef struct {
	vector_t origin;
	vector_t effector;
	vector_t j1[2];
	vector_t j2[2];
	double len[2];
	double total_len;
	double q[3];
	double error;
} manipulator_t;

void
manipulator_init(manipulator_t *m) {
	vector_init_d(&m->origin, 0, 0, 0);
	m->q[0] = 0.0 * M_PI / 180;
	m->q[1] = 45.0 * M_PI / 180;
	m->q[2] = 45.0 * M_PI / 180;
	m->len[0] = 40.0;
	m->len[1] = 30.0;
	m->error = 0.01;
	m->total_len = m->len[0] + m->len[1];
	vector_init_v(&m->j1[0], m->origin);
	vector_init_d(&m->j1[1],
				m->len[0] * cos(m->q[1]) * cos(m->q[0]),
				m->len[0] * sin(m->q[1]),
				m->len[0] * cos(m->q[1]) * sin(m->q[0]));
	vector_init_v(&m->j2[0], m->j1[1]);
	vector_init_d(&m->j2[1],
				(m->len[0] * cos(m->q[1]) + m->len[1] * cos(m->q[1] - m->q[2])) * cos(m->q[0]),
				m->len[0] * sin(m->q[1]) + m->len[1] * sin(m->q[1] - m->q[2]),
				(m->len[0] * cos(m->q[1]) + m->len[1] * cos(m->q[1] - m->q[2])) * sin(m->q[0]));
	vector_init_v(&m->effector, m->j2[1]);
}

void
manipulator_print(manipulator_t m) {
	printf("{\n");
	printf("q1 =\t%lfdeg\n", m.q[0] * 180 / M_PI);
	printf("q2 =\t%lfdeg\n", m.q[1] * 180 / M_PI);
	printf("q3 =\t%lfdeg\n", m.q[2] * 180 / M_PI);
	printf("\nm.origin =\t");
	vector_print(m.origin);
	printf("\nm.effector =\t");
	vector_print(m.effector);
	printf("\nm.j1[0] =\t");
	vector_print(m.j1[0]);
	printf("\nm.j1[1] =\t");
	vector_print(m.j1[1]);

	printf("\n\nm.j2[0] =\t");
	vector_print(m.j2[0]);
	printf("\nm.j2[1] =\t");
	vector_print(m.j2[1]);
	printf("\n}\n");
}

void
manipulator_forward(manipulator_t *m, int depth, double x, double y, double z);

void
manipulator_backward(manipulator_t *m, int depth, double x, double y, double z) {
	vector_init_d(&m->j2[1], x, y, z);
	if (vector_mag(m->j2[1]) > m->total_len) {
		printf("za daleko\n");
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
	printf("forward\n");
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
	// might do that forward has to be computed x times - TODO
	vector_init_d(&tmp, x, y, z);
	vector_sub(&tmp, tmp, m->j2[1]);
	//if (fabs(vector_mag(tmp)) > m->error || depth >= 0) {
	if (fabs(vector_mag(tmp)) > m->error) {
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
	m->q[1] = vector_angle(x_tmp, m->j1[1]);
	m->q[2] = m->q[1] + vector_angle(x_tmp, y_tmp);
	//manipulator_print(*m);
}


int
main() {
	manipulator_t milo;
	manipulator_init(&milo);
	manipulator_print(milo);
	milo.effector.x = 20;
	milo.effector.y = 29;

	manipulator_backward(&milo, 5, milo.effector.x, milo.effector.y, milo.effector.z);
	manipulator_calculate_angles(&milo);
	manipulator_print(milo);
	
	/*
	for (int i = 0; i <= 30; i++) {
		manipulator_backward(&milo, 5, milo.effector.x - i, milo.effector.y, milo.effector.z);
		manipulator_calculate_angles(&milo);
		manipulator_print(milo);
	}
	*/
}

