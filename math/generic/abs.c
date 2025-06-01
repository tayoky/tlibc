#include <math.h>
#include <limits.h>

//NOTE integer abs (abs labs llabs) are in stdlib not in math

#define template(type,name) type name(type x){\
	if(isnan(x))return x;\
	return signbit(x) ? -x : x;\
}

template(float,fabsf)
template(double,fabs)
template(long double,fabsl)
