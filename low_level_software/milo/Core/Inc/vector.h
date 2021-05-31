#ifndef INC_VECTOR_H_
#define INC_VECTOR_H_

#include <math.h>

typedef struct {
	double x;
	double y;
	double z;
} vector_t;

void
vector_init_d(vector_t *v, double x, double y, double z);

void
vector_init_v(vector_t *v, vector_t src);

void
vector_print(vector_t v);

double
vector_mag(vector_t v);

double
vector_dot(vector_t vec1, vector_t vec2);

double
vector_angle(vector_t vec1, vector_t vec2);

void
vector_add(vector_t *v, vector_t vec1, vector_t vec2);

void
vector_sub(vector_t *v, vector_t vec1, vector_t vec2);

void
vector_mult(vector_t *v, double num);

void
vector_normalize(vector_t *v);

#endif
