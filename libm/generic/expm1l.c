#include <math.h>

long double expm1l(long double x) {
	return expl(x) - 1.0;
}
