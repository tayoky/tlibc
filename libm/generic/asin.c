#include <math.h>
#include "internal.h"

float asinf(float x) {
#ifdef HAVE_BUILTIN_ASINF
	return __builtin_asinf(x);
#else
	// TODO : actual asinf impl
#endif
}

double asin(double x) {
#ifdef HAVE_BUILTIN_ASIN
	return __builtin_asin(x);
#else
	// TODO : actual asin impl
#endif
}
