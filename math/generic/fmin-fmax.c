#include <math.h>

//minl/maxl are in another file

#define template(type,name) type fmin##name(type a,type b){\
	return a < b ?  a : b;\
}\
type fmax##name(type a,type b){\
	return a > b ?  a : b;\
}

template(float,f)
template(double,)
