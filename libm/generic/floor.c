#include <string.h>
#include <math.h>
#include "internal.h"

double floor(double x) {
	uintdbl_t i;
	memcpy(&i, &x, sizeof(double));
	int e = (i >> DBL_MANT_BITS) & DBL_EXP_MASK;
	if (e == DBL_EXP_MASK) {
		// NAN or INFINITY
		return x;
	}

	uintdbl_t sign = i & DBL_SIGN_MASK;

	int exp = e - DBL_EXP_HALF;
	if (exp < 0) {
		// subnormal
		if (sign) {
			return i == DBL_SIGN_MASK ? -0.0 : -1.0;
		} else {
			return 0.0;
		}
	} else if (exp >= DBL_MANT_BITS) {
		// we don't have any fractional bits
		return x;
	}

	uintdbl_t fractional_mask = (1ULL << (DBL_MANT_BITS - exp)) - 1;
	if ((i & fractional_mask) == 0) {
		return x;
	}
	i &= ~fractional_mask;
	if (sign) {
		i += fractional_mask + 1;
	}
	memcpy(&x, &i, sizeof(double));
	return x;
}
