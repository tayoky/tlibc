#include <math.h>

long double log1pl(long double x) {
	return logl(1.0 + x);
}
