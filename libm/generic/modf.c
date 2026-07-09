#include <math.h>

double modf(double x, double *iptr) {
	if (isnan(x)) {
		*iptr = NAN;
		return x;
	}
	if (isinf(x)) {
		*iptr = x;
		return copysign(0, x);
	}
	long integral = trunc(x);
	*iptr = integral; 
	return x - fabs(integral);
}