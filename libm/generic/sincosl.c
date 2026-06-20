#include <math.h>

void sincosl(long double x, long double *sin, long double *cos) {
	*sin = sinl(x);
	*cos = cosl(x);
}
