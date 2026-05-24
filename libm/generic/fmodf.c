#include <math.h>
#include <limits.h>

float fmodf(float x, float y) {
	if (isnan(x) || isnan(y) || isinf(x) || y == 0) return NAN;
	if (isinf(y)) return x;
	float quotien = truncf(x / y);
	return x - quotien * y;
}
