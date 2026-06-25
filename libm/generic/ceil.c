#include <math.h>
#include <string.h>
#include "internal.h"

double ceil(double x) {
	uintdbl_t i;
	memcpy(&i, &x, sizeof(double));
	int e = (i >> DBL_MANT_BITS) & DBL_EXP_MASK;
	if (e == DBL_EXP_MASK) {
		// NAN or INFINITY
		return x;
	}

	uintdbl_t sign = i & DBL_SIGN_MASK;
	uintdbl_t mant = i & ((1ULL << DBL_MANT_BITS) - 1);

	int exp = e - DBL_EXP_HALF;
	if (exp < 0) {
		// subnormal
		return sign ? -0.0 : 1.0;
	} else if (exp >= DBL_MANT_BITS) {
		// we don't have any fractional bits
		return x;
	}

	uintdbl_t fractional_mask = (1ULL << (DBL_MANT_BITS - exp)) - 1;

	if ((mant & fractional_mask) == 0) {
		return x;
	}

	mant &= ~fractional_mask;

	if (!sign) {
		// increment integer part
		mant += fractional_mask + 1;
		if (mant >> DBL_MANT_BITS) {
			mant = 0;
			e++;
		}
	}

	i = sign | ((uintdbl_t)e << DBL_MANT_BITS) | mant;

	memcpy(&x, &i, sizeof(double));
	return x;
}
