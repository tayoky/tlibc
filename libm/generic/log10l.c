#include <math.h>
#include <errno.h>
#include "internal.h"

static const long double c[9] = {
	 0.4342944819032518,
	-0.2171472409516261,
	 0.1447648272911295,
	-0.1085736205727025,
	 0.0868589020959030,
	-0.0723824584281313,
	 0.0620413028236166,
	-0.0542385617260027,
	 0.0486111309867086,
};

// log10(2)
#define LOG10_2 0.3010299956639812

long double log10l(long double x) {
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
	long double m = frexp(x, &exp);

	// get closer to 0
	long double z = m - 1.0;

	// 9 degree minimax polyminal
	long double log_m = c[8];
	for (int i=7; i>=0; i--) {
		log_m = log_m * z + c[i];
	}
	log_m *= z;
	return log_m + (long double)exp * LOG10_2;
}
