#include <math.h>

double scalbn(double x, int exp) {
	return ldexp(x, exp);
}
