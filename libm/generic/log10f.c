#include <math.h>
#include <errno.h>
#include "internal.h"

static const float c[9] = {
	 0.4342944819032518f,
	-0.2171472409516261f,
	 0.1447648272911295f,
	-0.1085736205727025f,
	 0.0868589020959030f,
	-0.0723824584281313f,
	 0.0620413028236166f,
	-0.0542385617260027f,
	 0.0486111309867086f,
};

// log10(2)
#define LOG10_2 0.3010299956639812f

float log10f(float x) {
	if (isinf(x) || isnan(x)) {
		return x;
	}
	if (x <= 0) {
		if (x == 0) {
			// log10(0) is INFINITY
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
	float m = frexp(x, &exp);

	// get closer to 0
	float z = m - 1.0;

	// 9 degree minimax polyminal
	float log_m = c[8];
	for (int i=7; i>=0; i--) {
		log_m = log_m * z + c[i];
	}
	log_m *= z;
	return log_m + (float)exp * LOG10_2;
}
