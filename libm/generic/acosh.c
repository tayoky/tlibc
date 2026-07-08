#include <math.h>

double acosh(double x) {
	if (isnan(x)) return x;
	return log(x + sqrt(x * x - 1.0));
}
