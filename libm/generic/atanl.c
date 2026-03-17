#include <math.h>
#include "internal.h"

long double atanl(long double x) {
#ifdef HAVE_BUILTIN_ATANL
	return __builtin_atanl(x);
#else
	// TODO : actual atanl impl
#endif
}
