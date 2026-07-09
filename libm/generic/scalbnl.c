#include <math.h>

long double scalbnl(long double x, int exp) {
	return ldexpl(x, exp);
}
