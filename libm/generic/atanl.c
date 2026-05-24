#include <math.h>

#define TAN_PI_8  0.41421356237309504
#define TAN_3PI_8 2.414213562373095

static const long double c[5] = {
	 0.3333333333333333,
	-0.1999999999999995,
	 0.1428571428570304,
	-0.1111111111003425,
	 0.0909090902647464,
};

static long double atan_core(long double z) {
	long double z2 = z * z;
	long double z3 = z2 * z;

	// 9 degrees polyminal
	long double ret = c[4];
	for (int i = 3; i >= 0; i--) {
		ret = ret * z2 + c[i];
	}
	return z - (z3 * ret);
}

long double atanl(long double x) {
	if (isnan(x)) return x;

	long double sign = 1.0;
	if (x < 0.0) {
		x = -x;
		sign = -1.0;
	}

	if (isinf(x)) return M_PI_2 * sign;

	if (x < TAN_PI_8) {
		return atan_core(x) * sign;
	} else if (x < TAN_3PI_8) {
		long double t = (x - 1.0)/(x + 1.0);
		return (M_PI_4 + atan_core(t)) * sign;
	} else {
		long double t = 1.0 / x;
		return (M_PI_2 - atan_core(t)) * sign;
	}
}
