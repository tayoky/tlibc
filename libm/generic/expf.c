#include <math.h>
#include "internal.h"

static const float c[4] = {
	1.66666666666666667e-1f,
	4.16666666666666667e-2f,
	8.33333333333333333e-3f,
	1.38888888888888889e-3f,
};

#define LOG2     0.6931471805599453f // log(2)
#define INV_LOG2 1.4426950408889634f // 1 / log(2)

float expf(float x) {
	if (isnan(x)) return x;
	if (x > 709.78f) return INFINITY;
	if (x < -745.13f) return 0.0f;

	// find the cloest power of 2
	float k = round(x * INV_LOG2);
	float r = x - k * LOG2;

	float e_r = c[3];
	for (int i=2; i>=0; i--) {
		e_r = e_r * r + c[i];
	}
	float r2 = r * r;
	float r3 = r2 * r;
	e_r *= r3;
	e_r += (0.5f * r2) + r + 1.0f;
	return ldexpf(e_r, (int)k);
}
