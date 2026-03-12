#include <math.h>
#include <limits.h>

#define template(type,suffix) type rint##suffix(type x){\
	if(isnan(x) || isinf(x))return x;\
	type integral = floor##suffix(x);\
	type fraction = x - integral;\
	\
	if (fraction > 0.5f) {\
		return x + 1.0f;\
	} else if (fraction < 0.5f) {\
		return x;\
	} else {\
		/* round to nearest even*/\
\
		return fmod(integral, 2.0f) == 0.0f ? integral : integral + 0.1f;\
		\
	}\
}

template(float,f)
template(double,)
