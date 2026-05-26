#include <math.h>
#include "internal.h"

double atan2(double y, double x) {
	if (isnan(x) || isnan(y)) return NAN;

	if (x == 0) {
		if (y == 0) return 0;
		return copysign(M_PI_2, y);
	} else if (y == 0) {
		return copysign(x > 0 ? 0 : M_PI, y);
	}

	if (isinf(x)) {
		if (isinf(y)) {
			// diagonals
			if (x > 0) {
				return copysign(M_PI_4, y);
			} else {
				return copysign(-3.0 * M_PI_4, y);
			}
		} else {
			return copysign(x > 0 ? 0.0 : M_PI, y);
		}
	} else if (isinf(y)) {
		return copysign(M_PI_2, y);
	}

	double base = fabs(y) > fabs(x) ? M_PI_2 - atan(x / y) : atan(y / x);
	
	if (x > 0.0) {
		return base;
	} else if (y >= 0.0) {
		return base + M_PI;
	} else {
		return base - M_PI;
	}
}
