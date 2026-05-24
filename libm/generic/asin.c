#include <math.h>
#include <errno.h>
#include "internal.h"

static const double P[] = {
	 0.16666666666666666,
	-0.01249999999757921,
};

static const double Q[] = {
	 1.0,
	-0.2142857141014798,
};

// i found this online
static double asin_core(double x) {
	double x2 = x * x;
	double x3 = x2 * x;

	// evaluate the rational polynomial P(x^2) / Q(x^2) via Horner's Method
	double num = P[0] + x2 * P[1];
	double den = Q[0] + x2 * Q[1];

	return x + (x3 * (num / den));
}

double asin(double x) {
	if (isnan(x)) return x;

	if (x > 1.0 || x < -1.0) {
		errno = EDOM;
		return NAN;
	}

	double sign = 1.0;
	if (x < 0) {
		x = -x;
		sign = -1.0;
	}

	// fast path
	if (x == 0) return 0.0;
	if (x == 1.0) return sign * M_PI_2;

	if (x <= 0.5) {
		// central zone
		return sign * asin_core(x);
	} else {
		// edge zone
		double t = sqrt(0.5 * (1.0 - x));

		// scale the result back
		return sign * (M_PI_2 - 2.0 * asin_core(t));
	}
}
