#include <math.h>

long double fabsl(long double x){
	if(isnan(x)) return x;
	return signbit(x) ? -x : x;
}
