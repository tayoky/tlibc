#include <string.h>
#include <math.h>
#include "internal.h"

float floorf(float x) {
	uintflt_t i;
	memcpy(&i, &x, sizeof(float));
	int e = (i >> FLT_MANT_BITS) & FLT_EXP_MASK;
	if (e == FLT_EXP_MASK) {
		// NAN or INFINITY
		return x;
	}

	uintflt_t sign = i & FLT_SIGN_MASK;

	int exp = e - FLT_EXP_HALF;
	if (exp < 0) {
		// subnormal
		if (sign) {
			return i == FLT_SIGN_MASK ? -0.0 : -1.0;
		} else {
			return 0.0;
		}
	} else if (exp >= FLT_MANT_BITS) {
		// we don't have any fractional bits
		return x;
	}

	uintflt_t fractional_mask = (1ULL << (FLT_MANT_BITS - exp)) - 1;
	if ((i & fractional_mask) == 0) {
		return x;
	}
	i &= ~fractional_mask;
	if (sign) {
		i += fractional_mask + 1;
	}
	memcpy(&x, &i, sizeof(float));
	return x;
}
