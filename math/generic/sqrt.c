#include <math.h>

//simple generic sqrt implementation
//praticly never used since x86_64 and aarch64 provide their own hardware accelerated sqrt
//NOTE : because a lot of plateform don't have an hardware sqrtl,
//sqrtl in in generic/sqrtl.c

//we are going to use binary search
#define template(type,name) type name(type x){\
	if(signbit(x)) return NAN;\
\
	type start,end;\
	if(x < 1){\
		start = x;\
		end = 1;\
	} else {\
		start = 1;\
		end = x;\
	}\
\
	for(int i=0; i<20; i++){\
		type n = (start + end)/2;\
		type result = n * n;\
		if(result == x){\
			return n;\
		}\
		if(result < x){\
			start = n;\
		} else {\
			end = n;\
		}\
	}\
	return n;\
}

template(float,sqrtf)
template(double,sqrt)
