#include <math.h>
#include "internal.h"

long double atan2l(long double y, long double x) {
	if (isnan(x) || isnan(y)) return NAN;

	if (x == 0) {
		if (y == 0) return 0;
		return copysignl(M_PI_2, y);
	} else if (y == 0) {
		return copysignl(x > 0 ? 0 : M_PI, y);
	}

	if (isinf(x)) {
		if (isinf(y)) {
			// diagonals
			if (x > 0) {
				return copysignl(M_PI_4, y);
			} else {
				return copysignl(-3.0 * M_PI_4, y);
			}
		} else {
			return copysignl(x > 0 ? 0.0 : M_PI, y);
		}
	} else if (isinf(y)) {
		return copysignl(M_PI_2, y);
	}

	long double base = fabsl(y) > fabsl(x) ? M_PI_2 - atanl(x / y) : atanl(y / x);
	
	if (x > 0.0) {
		return base;
	} else if (y >= 0.0) {
		return base + M_PI;
	} else {
		return base - M_PI;
	}
}
