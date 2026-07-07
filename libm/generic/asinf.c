#include <math.h>
#include <errno.h>
#include "internal.h"

static const float P[] = {
	 0.1666666716f,
	-3.1417034566e-02f,
};

static const float Q[] = {
	 1.0f,
	-3.2676747441e-01f,
};

// i found this online
static float asin_core(float x) {
	float x2 = x * x;
	float x3 = x2 * x;

	// evaluate the rational polynomial P(x^2) / Q(x^2) via Horner's Method
	float num = P[0] + x2 * P[1];
	float den = Q[0] + x2 * Q[1];

	return x + (x3 * (num / den));
}

float asinf(float x) {
	if (isnan(x)) return x;

	if (x > 1.0f || x < -1.0f) {
		errno = EDOM;
		return NAN;
	}

	float sign = 1.0f;
	if (x < 0) {
		x = -x;
		sign = -1.0f;
	}

	// fast path
	if (x == 0) return 0.0f;
	if (x == 1.0f) return sign * M_PI_2;

	if (x <= 0.5f) {
		// central zone
		return sign * asin_core(x);
	} else {
		// edge zone
		float t = sqrtf(0.5f * (1.0f - x));

		// scale the result back
		return sign * (M_PI_2 - 2.0f * asin_core(t));
	}
}
