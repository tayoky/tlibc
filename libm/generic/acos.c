#include <math.h>
#include "internal.h"

float acosf(float x) {
#ifdef HAVE_BUILTIN_ACOSF
	return __builtin_acosf(x);
#else
	// TODO : actual acosf impl
#endif
}

double acos(double x) {
#ifdef HAVE_BUILTIN_ACOS
	return __builtin_acos(x);
#else
	// TODO : actual acos impl
#endif
}
