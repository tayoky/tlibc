#include <math.h>

long double roundl(long double x){
	if (isnan(x) || isinf(x)) return x;
	return x > 0.0f ? floorl(x + 0.5f) : ceill(x - 0.5f);
}
