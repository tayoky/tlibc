#include <string.h>
#include <math.h>
#include "internal.h"

float truncf(float x) {
	uintflt_t i;
	memcpy(&i, &x, sizeof(float));
	int e = (i >> FLT_MANT_BITS) & FLT_EXP_MASK;
	if (e == FLT_EXP_MASK) {
		// NAN or INFINITY
		return x;
	}

	int exp = e - FLT_EXP_HALF;
	if (exp < 0) {
		// subnormal
		return x < 0 ? -0.0f : 0.0f;
	} else if (exp >= FLT_MANT_BITS) {
		// we don't have any fractional bits
		return x;
	}
	uintflt_t fractional_mask = (1ULL << (FLT_MANT_BITS - exp)) - 1;
	i &= ~fractional_mask;
	memcpy(&x, &i, sizeof(float));
	return x;
}
