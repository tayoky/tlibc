#include <math.h>

//use binary search
long double sqrtl(long double x){
	if(signbit(x)) return NAN;

	long double start = 0;
	long double end = x;

	for(int i=0; i<20; i++){
		long double n = (start + end)/2;
		long double result = n * n;
		if(result == x){
			return n;
		}
		if(result < x){
			start = n;
		} else {
			end = n;
		}
	}
	return (start + end)/2;
}
