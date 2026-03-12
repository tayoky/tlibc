#include <math.h>
#include <limits.h>

#define template(type,name) type name(type x, type y){\
	if (isnan(x) || isnan(y) || isinf(x) || y == 0)return NAN;\
	if (isinf(y)) return x;\
	type quotien = (long long)(x / y);\
	return x - quotien * y;\
}

template(float,fmodf)
template(double,fmod)
