#include <math.h>
#include <limits.h>

long double fmodl(long double x, long double y){
	if (isnan(x) || isnan(y) || isinf(x) || y == 0)return NAN;
	if (isinf(y)) return x;
	long double quotien = (long long)(x / y);
	return x - quotien * y;
}
