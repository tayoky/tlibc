#include <math.h>
#include "internal.h"

float atan2f(float y, float x) {
	if (isnan(x) || isnan(y)) return NAN;

	if (x == 0) {
		if (y == 0) return 0;
		return copysignf(M_PI_2, y);
	} else if (y == 0) {
		return copysignf(x > 0 ? 0 : M_PI, y);
	}

	if (isinf(x)) {
		if (isinf(y)) {
			// diagonals
			if (x > 0) {
				return copysignf(M_PI_4, y);
			} else {
				return copysignf(-3.0 * M_PI_4, y);
			}
		} else {
			return copysignf(x > 0 ? 0.0 : M_PI, y);
		}
	} else if (isinf(y)) {
		return copysignf(M_PI_2, y);
	}

	float base = fabsf(y) > fabsf(x) ? M_PI_2 - atanf(x / y) : atanf(y / x);
	
	if (x > 0.0) {
		return base;
	} else if (y >= 0.0) {
		return base + M_PI;
	} else {
		return base - M_PI;
	}
}
