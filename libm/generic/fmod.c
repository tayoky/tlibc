#include <math.h>
#include <limits.h>

double fmod(double x, double y) {
	if (isnan(x) || isnan(y) || isinf(x) || y == 0) return NAN;
	if (isinf(y)) return x;
    double q = x / y;
    double n = (q > 0) ? floor(q) : ceil(q);

    return x - n * y;
}
