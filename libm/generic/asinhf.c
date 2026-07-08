#include <math.h>

float asinhf(float x) {
	if (isnan(x)) return x;
	return logf(x + sqrtf(x * x + 1.0f));
}
