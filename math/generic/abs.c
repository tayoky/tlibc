#include <math.h>
#include <limits.h>

//very basic math

//abs

//no need to do classic abs it's aready in stdlib

#define xabs(type,name) type name(type x){\
	type mask = x >> ((sizeof(type) * CHAR_BIT) - 1);\
	return (x^mask) - mask;\
}

xabs(long,labs)
xabs(long long,llabs)


double fabs(double x){
	if(x < 0){
		return -x;
	} else {
		return x;
	}
}

long double fabsl(long double x){
	if(x < 0){
		return -x;
	} else {
		return x;
	}
}

float fabsf(float x){
	if(x < 0){
		return -x;
	} else {
		return x;
	}
}
