#include <math.h>

//very basic math

//abs

//no need to do classic abs it's aready in stdlib

long labs(long x){
	long mask = x >> 63;
	return (x^mask) + mask;
}

long long llabs(long long x){
	long long mask = x >> (sizeof(x) * 8 -1);
	return (x^mask) + mask;
}


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
