#include <string.h>
#include <math.h>
#include "internal.h"

float frexpf(float x, int *exp) {
	uintflt_t i;
	memcpy(&i, &x, sizeof(float));
	int e = (i >> FLT_MANT_BITS) & FLT_EXP_MASK;
	if (e == FLT_EXP_MASK) {
		// NAN or INFINITY
		return x;
	}
	if (e == 0) {
		if ((i & FLT_MANT_MASK) == 0) {
			// zero
			*exp = 0;
			return x;
		} else {
			// subnormal
			x *= 3.3554432e+07f;
			memcpy(&i, &x, sizeof(float));
			e = (i >> FLT_MANT_BITS) & FLT_EXP_MASK;
			*exp = e - FLT_EXP_HALF - 25;
		}
	} else {
		// normal
		*exp = e - FLT_EXP_HALF;
	}

	// extract mantisse
	i &= ~(FLT_EXP_MASK << FLT_MANT_BITS);
	i |= FLT_EXP_HALF << FLT_MANT_BITS;
	memcpy(&x, &i, sizeof(float));
	return x;
}
