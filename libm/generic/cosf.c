#include <math.h>

static float cos_core(float x) {
	float x2 = x * x;
	return 1 - x2 * (0.5f - x2 * (4.1666666666666664e-2f - x2 * (1.3888888888888889e-3f - x2 * (2.48015873015873e-5f))));
}

static float sin_core(float x) {
	float x2 = x * x;
	return x * (1.0f - x2 * (1.6666666666666666e-1f - x2 * (8.3333333333333333e-3f - x2 * (1.9841269841269841e-4f - x2 * (2.7557319223985893e-6f)))));
}

static float rem2pi(float x, int *q) {
	// reduce to quadrant index
	long k = (long)floorf(x * M_2_PI);

	float r = x - k * M_PI_2;

	// fix rounding issues
	if (r >= (float)M_PI_2) {
		r -= M_PI_2;
		k++;
	} else if (r < 0) {
		r += M_PI_2;
		k--;
	}

	*q = k & 3;
	return r;
}

float cosf(float x) {
	if (isnan(x)) return x;
	if (isinf(x)) return NAN;


	int q;
	float r = rem2pi(x, &q);

	switch (q) {
	case 0:
		return cos_core(r);
	case 1:
		return -sin_core(r);
	case 2:
		return -cos_core(r);
	default:
		return sin_core(r);
	}
}

float sinf(float x) {
	if (isnan(x)) return x;
	if (isinf(x)) return NAN;

	int q;
	float r = rem2pi(x, &q);

	switch (q) {
	case 0:
		return sin_core(r);
	case 1:
		return cos_core(r);
	case 2:
		return -sin_core(r);
	default:
		return -cos_core(r);
	}
}

float tanf(float x) {
	return sinf(x) / cosf(x);
}
