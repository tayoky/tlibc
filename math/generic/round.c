#include <math.h>

#define template(type,name) type round##name(type x){\
	return floor##name(x + 0.5f);\
}

template(float,f)
template(double,)
