#include <math.h>

#define template(type,name) type round##name(type x){\
	if (isnan(x) || isinf(x)) return x;\
	return x > 0.0f ? floor##name(x + 0.5f) : ceil##name(x - 0.5f);\
}

template(float,f)
template(double,)
