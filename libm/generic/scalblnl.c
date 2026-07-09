#include <math.h>

long double scalblnl(long double x, long exp) {
	return ldexpl(x, exp);
}
