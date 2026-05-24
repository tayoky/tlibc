#include <string.h>
#include <math.h>
#include "internal.h"

double trunc(double x) {
	uintdbl_t i;
	memcpy(&i, &x, sizeof(double));
	int e = (i >> DBL_MANT_BITS) & DBL_EXP_MASK;
	if (e == DBL_EXP_MASK) {
		// NAN or INFINITY
		return x;
	}

	int exp = e - DBL_EXP_HALF;
	if (exp < 0) {
		// subnormal
		return x < 0 ? -0.0 : 0.0;
	} else if (exp >= DBL_MANT_BITS) {
		// we don't have any fractional bits
		return x;
	}
	uintdbl_t fractional_mask = (1ULL << (DBL_MANT_BITS - exp)) - 1;
	i &= ~fractional_mask;
	memcpy(&x, &i, sizeof(double));
	return x;
}
