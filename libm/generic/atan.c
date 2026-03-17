#include <math.h>
#include "internal.h"

float atanf(float x) {
#ifdef HAVE_BUILTIN_ATANF
	return __builtin_atanf(x);
#else
	// TODO : actual atanf impl
#endif
}

double atan(double x) {
#ifdef HAVE_BUILTIN_ATAN
	return __builtin_atan(x);
#else
	// TODO : actual atan impl
#endif
}
