#include <math.h>
#include <limits.h>

float fmodf(float x, float y) {
	if (isnan(x) || isnan(y) || isinf(x) || y == 0) return NAN;
	if (isinf(y)) return x;
    float q = x / y;
    float n = (q >= 0.0f) ? floorf(q) : ceilf(q);

    return x - n * y;
}
