#include <math.h>
#include "internal.h"

long double atan2l(long double x, long double y) {
#ifdef HAVE_BUILTIN_ATAN2L
	return __builtin_atan2l(x, y);
#else
	// TODO : actual atan2l impl
#endif
}
