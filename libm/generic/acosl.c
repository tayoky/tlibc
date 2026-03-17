#include <math.h>
#include "internal.h"

long double acosl(long double x) {
#ifdef HAVE_BUILTIN_ACOSL
	return __builtin_acosl(x);
#else
	// TODO : actual acosl impl
#endif
}
