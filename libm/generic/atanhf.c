#include <math.h>

float atanhf(float x) {
	if (isnan(x)) return x;
	return 0.5f * logf((1.0f + x) / (1.0f - x));
}
