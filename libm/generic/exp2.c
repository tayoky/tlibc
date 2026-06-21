#include <math.h>

double exp2(double x) {
	if (isnan(x)) return x;

	// TODO
	return ldexp(1, (int)x);
}