#include <math.h>

//ceill is separeted since some plateform provide ceil and ceilf but not ceill

long double ceill(long double x){
	if(x >= (long double)LLONG_MAX || x <= (long double)LLONG_MIN || isnan(x) || isinf(x)){
		return x;
	}
	return signbit(x) ? -((long long)-x) - 1  : -((long long)-x);
}
