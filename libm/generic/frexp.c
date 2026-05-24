#include <string.h>
#include <math.h>
#include "internal.h"

double frexp(double x, int *exp) {
	uintdbl_t i;
	memcpy(&i, &x, sizeof(double));
	int e = (i >> DBL_MANT_BITS) & DBL_EXP_MASK;
	if (e == DBL_EXP_MASK) {
		// NAN or INFINITY
		return x;
	}
	if (e == 0) {
		if ((i & DBL_MANT_MASK) == 0) {
			// it's zero
			*exp = 0;
			return x;
		} else {
			// subnormal
			x *= 1.8014398509481984e+16; // 2 ^ 54
			memcpy(&i, &x, sizeof(double));
			e = (i >> DBL_MANT_BITS) & DBL_EXP_MASK;
			*exp = e - DBL_EXP_HALF - 54;
		}
	} else {
		// normal
		*exp = e - DBL_EXP_HALF;
	}

	// extract mantisse
	i &= ~(DBL_EXP_MASK << DBL_MANT_BITS);
	i |= DBL_EXP_HALF << DBL_MANT_BITS;
	memcpy(&x, &i, sizeof(double));
	return x;
}
