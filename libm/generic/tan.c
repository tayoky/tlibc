#include <math.h>

float tanf(float x) {
#ifdef HAVE_BUILTIN_TANF
	return __builtin_tanf(x);
#else
	return sinf(x) / cosf(x);
#endif
}

double tan(double x) {
#ifdef HAVE_BUILTIN_TAN
	return __builtin_tan(x);
#else
	return sin(x) / cos(x);
#endif
}

long double tanl(long double x) {
#ifdef HAVE_BUILTIN_TANL
	return __builtin_tanl(x);
#else
	return sinl(x) / cosl(x);
#endif
}
