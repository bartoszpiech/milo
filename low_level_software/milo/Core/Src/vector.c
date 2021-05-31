#include "vector.h"

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
