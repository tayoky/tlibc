#include <string.h>
#include <math.h>
#include <errno.h>
#include "internal.h"

float ldexpf(float x, int exp) {
	uintflt_t i;
	memcpy(&i, &x, sizeof(float));
	int e = (i >> FLT_MANT_BITS) & FLT_EXP_MASK;
	if (e == FLT_EXP_MASK) {
		// NAN or INFINITY
		return x;
	}
	if (e == 0) {
		if (x == 0) {
			// zero
			return x;
		} else {
			// subnormal
			x *= 3.3554432e+07f; // 2 ^ 25
			memcpy(&i, &x, sizeof(float));
			e = ((i >> FLT_MANT_BITS) & FLT_EXP_MASK) - FLT_MANT_DIG - 1;
		}
	}

	// combine exponents
	exp += e;

	// exponent overflow
	if (exp >= (int)FLT_EXP_MASK) {
		errno = ERANGE;
		// set to infinity but keep sign
		i &= FLT_SIGN_MASK;
		i |= FLT_EXP_MASK << FLT_MANT_BITS;
		memcpy(&x, &i, sizeof(float));
		return x;
	}

	// exponent underflow
	if (exp <= 0) {
		if (exp < -FLT_MANT_DIG) {
			// zero but keep sign
			i &= FLT_SIGN_MASK;
			memcpy(&x, &i, sizeof(float));
			return x;
		} else {
			// we need to return a subnormal
			exp += FLT_MANT_DIG + 1;

			// set the new exponent
			i &= ~(FLT_EXP_MASK << FLT_MANT_BITS);
			i |= ((uintflt_t)exp) << FLT_MANT_BITS;
			memcpy(&x, &i, sizeof(float));
			return x * 2.98023224e-08f; // 2 ^ -25
		}
	}

	// set the new exponent
	i &= ~(FLT_EXP_MASK << FLT_MANT_BITS);
	i |= ((uintflt_t)exp) << FLT_MANT_BITS;
	memcpy(&x, &i, sizeof(float));
	return x;
}
