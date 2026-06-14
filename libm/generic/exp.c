#include <math.h>
#include "internal.h"

static const double c[4] = {
	1.66666666666666667e-1,
	4.16666666666666667e-2,
	8.33333333333333333e-3,
	1.38888888888888889e-3,
};

#define LOG2     0.6931471805599453 // log(2)
#define INV_LOG2 1.4426950408889634 // 1 / log(2)

double exp(double x) {
	if (isnan(x)) return x;
	if (x > 709.78) return INFINITY;
	if (x < -745.13) return 0.0;

	// find the cloest power of 2
	double k = round(x * INV_LOG2);
	double r = x - k * LOG2;

	double e_r = c[3];
	for (int i=2; i>=0; i--) {
		e_r = e_r * r + c[i];
	}
	double r2 = r * r;
	double r3 = r2 * r;
	e_r *= r3;
	e_r += (0.5 * r2) + r + 1.0;
	return ldexp(e_r, (int)k);
}
