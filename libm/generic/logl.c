#include <math.h>
#include <errno.h>
#include "internal.h"

static const long double c[9] = {
	 1.0000000000000000,
	-0.4999999999999273,
	 0.3333333333246374,
	-0.2499999997913075,
	 0.1999999933560647,
	-0.1666665796645320,
	 0.1428543419356191,
	-0.1249764516315570,
	 0.1107563467651877,
};

// log(2)
#define LOG2 0.6931471805599453

long double logl(long double x) {
	if (isinf(x) || isnan(x)) {
		return x;
	}
	if (x <= 0) {
		if (x == 0) {
			// log(0) is INFINITY
			return -INFINITY;
		} else {
			errno = EDOM;
			return NAN;
		}
	}
	// fast path log(1) is 0
	if (x == 1.0) {
		return 0;
	}
	int exp;
	long double m = frexpl(x, &exp);

	// get closer to 0
	long double z = m - 1.0;

	// 9 degree minimax polyminal
	long double log_m = c[8];
	for (int i=7; i>=0; i--) {
		log_m = log_m * z + c[i];
	}
	log_m *= z;
	return log_m + (long double)exp * LOG2;
}
