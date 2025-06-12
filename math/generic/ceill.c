#include <math.h>

//ceill is separeted since some plateform provide ceil and ceilf but not ceill

#define template(type,name) type name(type x){\
	if(x >= (type)LLONG_MAX || x <= (type)LLONG_MIN || isnan(x) || isinf(x)){\
		return x;\
	}\
	return signbit(x) ? -((long long)-x) - 1  : -((long long)-x);\
}

template(long double,ceill)
