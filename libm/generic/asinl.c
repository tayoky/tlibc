#include <math.h>
#include "internal.h"

long double asinl(long double x) {
#ifdef HAVE_BUILTIN_ASINL
	return __builtin_asinl(x);
#else
	// TODO : actual asinl impl
#endif
}
