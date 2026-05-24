#include <math.h>
#include <errno.h>
#include "internal.h"

static const float c[9] = {
	 1.4426950408889634, // 1/ln(2)
	-0.7213475204444817,
	 0.4808983469629871,
	-0.3606737602222409,
	 0.2885390081777927,
	-0.2404491763888941,
	 0.2060992828571401,
	-0.1803368801111198,
	 0.1603052267555543,
};

float log2f(float x) {
	if (isinf(x) || isnan(x)) {
		return x;
	}
	if (x <= 0) {
		if (x == 0) {
			// log2(0) is INFINITY
			return -INFINITY;
		} else {
			errno = EDOM;
			return NAN;
		}
	}
	int exp;
	float m = frexpf(x, &exp);

	// get closer to 0
	float z = m - 1.0;

	// 9 degree minimax polyminal
	float log2_m = c[8];
	for (int i=7; i>=0; i--) {
		log2_m = log2_m * z + c[i];
	}
	log2_m *= z;
	return (float)exp + log2_m;
}
