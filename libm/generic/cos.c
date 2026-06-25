#include <math.h>

static double cos_core(double x) {
    double x2 = x * x;
    return 1
        - x2 * (0.5
        - x2 * (4.1666666666666664e-2
        - x2 * (1.3888888888888889e-3
        - x2 * (2.48015873015873e-5))));
}

static double sin_core(double x) {
    double x2 = x * x;
    return x * (1
        - x2 * (1.6666666666666666e-1
        - x2 * (1.9841269841269841e-3
        - x2 * (2.755731922398589e-5
        - x2 * (2.505210838544172e-7)))));
}

static double rem2pi(double x, int *q) {
    // 2/π precomputed constant
    const double inv_pi_2 = 2.0 / M_PI;

    // reduce to quadrant index
    long k = (long)(x * inv_pi_2);

    double r = x - k * M_PI_2;

    // fix rounding issues
    if (r > M_PI_2) {
        r -= M_PI_2;
        k++;
    } else if (r < 0) {
        r += M_PI_2;
        k--;
    }

    *q = k & 3;
    return r;
}

double cos(double x) {
	if (isnan(x)) return x;
	if (isinf(x)) return NAN;


    int q;
    double r = rem2pi(x, &q);

    switch (q) {
        case 0: return cos_core(r);
        case 1: return -sin_core(r);
        case 2: return -cos_core(r);
        default:return sin_core(r);
    }
}

double sin(double x) {
	if (isnan(x)) return x;
	if (isinf(x)) return NAN;

	int q;
	double r = rem2pi(x, &q);

	switch (q) {
	case 0:
		return sin_core(r);
	case 1:
		return cos_core(r);
	case 2:
		return -sin_core(r);
	default:
		return -cos_core(r);
	}
}

double tan(double x) {
	return sin(x) / cos(x);
}
