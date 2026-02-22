#include <math.h>

#define template(type,name) type tan##name(type x){\
	return sin##name(x) / cos##name(x);\
}

template(float,f)
template(double,)
template(long double,l)
