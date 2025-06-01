#include <math.h>
#include <limits.h>

//we know that integer conversion do a floor
//we can negate the number so it does a ceil

#define template(type,name) type name(type x){\
	if(x >= (type)LLONG_MAX || x <= (type)LLONG_MIN || isnan(x) || isinf(x)){\
		return x;\
	}\
	return signbit(x) ? -((long long)-x) - 1  : -((long long)-x);\
}

template(float,ceilf)
template(double,ceil)
template(long double,ceill)
