#include <string.h>
#include <math.h>
#include "internal.h"

long double frexpl(long double x, int *exp) {
#if LDBL_MANT_DIG == DBL_MANT_DIG
	return frexp(x, exp);
#else
	// TODO
	return x;
#endif
}
