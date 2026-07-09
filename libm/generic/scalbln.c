#include <math.h>

double scalbln(double x, long exp) {
	return ldexp(x, exp);
}
