#include <stdio.h>
#include <math.h>

int main() {
	double x, y, z;
	double l1 = 40.0, l2 = 30.0;

	scanf("%lf", &x);
	scanf("%lf", &y);
	scanf("%lf", &z);

	double q1, q2, q3;

	q3 = acos(	(x * x + y * y + z * z - (l1 * l1) - (l2 * l2)) /
				(2 * l1 * l2));

	q2 = asin(	(y * y - l2 * l2 * sin(q3) * sin(q3)) /
				(l1 * l1 + l2 * l2 * cos(q3) * cos(q3) + 2 * l1 * l2 * cos(q3) - l2 * l2 * sin(q3) * sin(q3)));

	q1 = acos(	x /
				(l1 * cos(q2) + l2 * cos(q2 + q3)));
	printf("q3 = %lf\n", q3 * 57.295779513);
	printf("q2 = %lf\n", q2 * 57.295779513);
	printf("q1 = %lf\n", q1 * 57.295779513);

	x = (l1 * cos(q2) + l2 * cos(q2 + q3)) * cos(q1);
	y = l1 * sin(q2) + l2 * sin(q2 + q3);
	z = (l1 * cos(q2) + l2 * cos(q2 + q3)) * sin(q1);
	printf("x = %lf\n", x);
	printf("y = %lf\n", y);
	printf("z = %lf\n", z);

}
