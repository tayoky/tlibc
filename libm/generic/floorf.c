#include <math.h>
#include <string.h>
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
	uintflt_t mant = i & ((1ULL << FLT_MANT_BITS) - 1);

	int exp = e - FLT_EXP_HALF;
	if (exp < 0) {
		// subnormal
		return sign ? -1.0 : 0.0;
	} else if (exp >= FLT_MANT_BITS) {
		// we don't have any fractional bits
		return x;
	}

	uintflt_t fractional_mask = (1ULL << (FLT_MANT_BITS - exp)) - 1;

	if ((mant & fractional_mask) == 0) {
		return x;
	}

	mant &= ~fractional_mask;

	if (sign) {
		// increment integer part
		mant += fractional_mask + 1;
		if (mant >> FLT_MANT_BITS) {
			mant = 0;
			e++;
		}
	}

	i = sign | ((uintflt_t)e << FLT_MANT_BITS) | mant;

	memcpy(&x, &i, sizeof(float));
	return x;
}
