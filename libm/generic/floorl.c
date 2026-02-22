#include <math.h>

//floorl is separated for the same reson as ceill
long double floorl(long double x){
	if(x >= (long double)LLONG_MAX || x <= (long double)LLONG_MIN || isnan(x) || isinf(x)){
		return x;
	}
	return signbit(x) ? ((long long)x)-1 : (long long) x;
}
