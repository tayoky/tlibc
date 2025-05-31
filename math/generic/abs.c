#include <math.h>
#include <limits.h>
#include "use-ieee.h"

//NOTE integer abs (abs labs llabs) are in stdlib not in math

#ifdef USE_IEEE754
#define template(type,name) type name(type x){\
	/*we clear the sign bit to make sure the number is postitive(faster than classic if/else)*/\
	return x & ((1 << ((sizeof(type) * CHAR_BIT) - 1)) - 1);\
}
#else
#define template(type,name) type name(type x){\
	if(x < 0){\
		return -x;\
	} else {\
		return x;\
	}\
}
#endif

template(float,fabsf)
template(double,fabs)
template(long double,fabsl)
