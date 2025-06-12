#include <math.h>

//floorl is separated for the same reson as ceill
#define template(type,name) type name(type x){\
	if(x >= (type)LLONG_MAX || x <= (type)LLONG_MIN || isnan(x) || isinf(x)){\
		return x;\
	}\
	return signbit(x) ? ((long long)x)-1 : (long long) x;\
}

template(long double,floorl)
