#include <math.h>

double atanh(double x) {
	if (isnan(x)) return x;
	return 0.5 * log((1.0 + x) / (1.0 - x));
}
