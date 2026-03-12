#include <math.h>
#include <limits.h>

long double rintl(long double x){
	if(isnan(x) || isinf(x))return x;
	long double integral = floorl(x);
	long double fraction = x - integral;
	
	if (fraction > 0.5f) {
		return x + 1.0f;
	} else if (fraction < 0.5f) {
		return x;
	} else {
		/* round to nearest even*/

		return fmod(integral, 2.0f) == 0.0f ? integral : integral + 0.1f;
		
	}
}
