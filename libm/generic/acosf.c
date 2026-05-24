#include <math.h>
#include "internal.h"

float acosf(float x) {
	float r = asinf(x);
	return isnan(r) ? r : M_PI_2 - r;
}
