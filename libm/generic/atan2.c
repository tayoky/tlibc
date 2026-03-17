#include <math.h>
#include "internal.h"

float atan2f(float x, float y) {
#ifdef HAVE_BUILTIN_ATAN2F
	return __builtin_atan2f(x, y);
#else
	// TODO : actual atan2f impl
#endif
}

double atan2(double x, double y) {
#ifdef HAVE_BUILTIN_ATAN2
	return __builtin_atan2(x, y);
#else
	// TODO : actual atan2 impl
#endif
}
