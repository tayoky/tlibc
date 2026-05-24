#include <math.h>
#include <errno.h>
#include "internal.h"

static const long double c[9] = {
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

long double log2l(long double x) {
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
	long double m = frexpl(x, &exp);

	// get closer to 0
	long double z = m - 1.0;

	// fast path, power of 2
	if (z == -0.5) {
		return (long double)exp - 1;
	}

	// 9 degree minimax polyminal
	long double log2_m = c[8];
	for (int i=7; i>=0; i--) {
		log2_m = log2_m * z + c[i];
	}
	log2_m *= z;
	return (long double)exp + log2_m;
}
