#include <math.h>
#include "internal.h"

double atan2(double y, double x) {
	if (isnan(x) || isnan(y)) return NAN;

	if (x == 0) {
		if (y > 0) return M_PI_2;
		if (y < 0) return -M_PI_2;
		return 0;
	}

	if (isinf(x)) {
		if (isinf(y)) {
			// diagonals
			if (x > 0) {
				return y > 0 ? M_PI_4 : -M_PI_4;
			} else {
				return y > 0 ? 3.0 * M_PI_4 : -3.0 * M_PI_4;
			}
		} else {
			return x > 0 ? 0.0 : M_PI;
		}
	} else {
		if (isinf(y)) {
			return y > 0 ? M_PI_2 : -M_PI_2;
		}
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
