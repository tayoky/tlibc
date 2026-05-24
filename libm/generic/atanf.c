#include <math.h>

#define TAN_PI_8  0.41421356237309504f
#define TAN_3PI_8 2.414213562373095f

static const float c[5] = {
	 0.3333333333333333f,
	-0.1999999999999995f,
	 0.1428571428570304f,
	-0.1111111111003425f,
	 0.0909090902647464f,
};

static float atan_core(float z) {
	float z2 = z * z;
	float z3 = z2 * z;

	// 9 degrees polyminal
	float ret = c[4];
	for (int i = 3; i >= 0; i--) {
		ret = ret * z2 + c[i];
	}
	return z - (z3 * ret);
}

float atanf(float x) {
	if (isnan(x)) return x;

	float sign = 1.0;
	if (x < 0.0) {
		x = -x;
		sign = -1.0;
	}

	if (isinf(x)) return M_PI_2 * sign;

	if (x < TAN_PI_8) {
		return atan_core(x) * sign;
	} else if (x < TAN_3PI_8) {
		float t = (x - 1.0)/(x + 1.0);
		return (M_PI_4 + atan_core(t)) * sign;
	} else {
		float t = 1.0 / x;
		return (M_PI_2 - atan_core(t)) * sign;
	}
}
