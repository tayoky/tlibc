#include <string.h>
#include <math.h>
#include <errno.h>
#include "internal.h"

double ldexp(double x, int exp) {
	uintdbl_t i;
	memcpy(&i, &x, sizeof(double));
	int e = (i >> DBL_MANT_BITS) & DBL_EXP_MASK;
	if (e == DBL_EXP_MASK) {
		// NAN or INFINITY
		return x;
	}
	if (e == 0) {
		if (x == 0) {
			// zero
			return x;
		} else {
			// subnormal
			x *= 1.8014398509481984e+16; // 2 ^ 54
			memcpy(&i, &x, sizeof(double));
			e = ((i >> DBL_MANT_BITS) & DBL_EXP_MASK) - DBL_MANT_DIG - 1;
		}
	}

	// combine exponents
	exp += e;

	// exponent overflow
	if (exp >= (int)DBL_EXP_MASK) {
		errno = ERANGE;
		// set to infinity but keep sign
		i &= DBL_SIGN_MASK;
		i |= DBL_EXP_MASK << DBL_MANT_BITS;
		memcpy(&x, &i, sizeof(double));
		return x;
	}

	// exponent underflow
	if (exp <= 0) {
		if (exp < -DBL_MANT_DIG) {
			// zero but keep sign
			i &= DBL_SIGN_MASK;
			memcpy(&x, &i, sizeof(double));
			return x;
		} else {
			// we need to return a subnormal
			exp += DBL_MANT_DIG + 1;

			// set the new exponent
			i &= ~(DBL_EXP_MASK << DBL_MANT_BITS);
			i |= ((uintdbl_t)exp) << DBL_MANT_BITS;
			memcpy(&x, &i, sizeof(double));
			return x * 5.551115123125783e-17; // 2 ^ -54
		}
	}

	// set the new exponent
	i &= ~(DBL_EXP_MASK << DBL_MANT_BITS);
	i |= ((uintdbl_t)exp) << DBL_MANT_BITS;
	memcpy(&x, &i, sizeof(double));
	return x;
}
