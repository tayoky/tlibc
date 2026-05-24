#include <math.h>
#include "internal.h"

double acos(double x) {
	double r = asin(x);
	return isnan(r) ? r : M_PI_2 - r;
}
