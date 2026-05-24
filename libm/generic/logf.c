#include <math.h>
#include <errno.h>
#include "internal.h"

static const float c[9] = {
	 1.0000000000000000f,
	-0.4999999999999273f,
	 0.3333333333246374f,
	-0.2499999997913075f,
	 0.1999999933560647f,
	-0.1666665796645320f,
	 0.1428543419356191f,
	-0.1249764516315570f,
	 0.1107563467651877f,
};

// log(2)
#define LOG2 0.6931471805599453f

float logf(float x) {
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
	if (x == 1.0f) {
		return 0;
	}
	int exp;
	float m = frexpf(x, &exp);

	// get closer to 0
	float z = m - 1.0f;

	// 9 degree minimax polyminal
	float log_m = c[8];
	for (int i=7; i>=0; i--) {
		log_m = log_m * z + c[i];
	}
	log_m *= z;
	return log_m + (float)exp * LOG2;
}
