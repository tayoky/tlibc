#include <math.h>
#include <limits.h>

//floorl is in another file
#define template(type,name) type name(type x){\
	if(x >= (type)LLONG_MAX || x <= (type)LLONG_MIN || isnan(x) || isinf(x)){\
		return x;\
	}\
	return signbit(x) ? ((long long)x)-1 : (long long) x;\
}

template(float,floorf)
template(double,floor)
