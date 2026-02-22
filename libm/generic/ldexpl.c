#include <math.h>
#include <errno.h>
#include "internal.h"

long double ldexpl(long double a, int exp) {
	if(exp > LDBL_MAX_EXP - 1 || exp < -LDBL_MAX_EXP){
		errno = ERANGE;
		return HUGE_VALL;
	}
	intldbl_t power = ((intldbl_t)(exp + LDBL_MAX_EXP - 1) << (LDBL_MANT_DIG - 1));
	return a * (*(long double*) &power);
}
