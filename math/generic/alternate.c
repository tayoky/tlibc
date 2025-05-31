#include <math.h>

//define alternative type for function
//eg sqrtf for sqrt

#define alt(name) float name##f(float x){\
	return (float)name((double)x);\
}\
long double name##l(long double x){\
	return (long double)name((double)x);\
}

alt(sqrt)
