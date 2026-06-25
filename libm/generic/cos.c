#include <math.h>

// constants taken from FreeBSD
static const double c[] = {
	 4.16666666666666019037e-02,
	-1.38888888888741095749e-03,
	 2.48015872894767294178e-05,
	-2.75573143513906633035e-07,
	 2.08757232129817482790e-09,
	-1.13596475577381996161e-11,
};

static double cos_core(double x) {
	double x2 = x * x;
	double x4 = x2 * x2;

	// minimax polyminal using Horner's Method
	double res = c[5];
	for (int i = 4; i >= 0; i--) {
		res = res * x2 + c[i];
	}
	res *= x4;
	return 1.0 - x2 / 2.0 + res;
}

// constants taken from FreeBSD
static const double s[] = {
	-1.66666666666666324348e-01,
	 8.33333333332248946124e-03,
	-1.98412698298579493134e-04,
	 2.75573137070700676789e-06,
	-2.50507602534068634195e-08,
	 1.58969099521155010221e-10,
};

static double sin_core(double x) {
	double x2 = x * x;
	double x3 = x2 * x;

	// minimax polyminal using Horner's Method
	double res = s[5];
	for (int i = 4; i >= 0; i--) {
		res = res * x2 + s[i];
	}
	return x + x3 * res;
}

double cos(double x) {
	if (isnan(x)) return x;
	if (isinf(x)) return NAN;

	x = fmod(x, 2.0 * M_PI);
	if (x < 0) x += 2.0 * M_PI;

	if (x <= M_PI_4) {
		return cos_core(x);
	} else if (x <= 3.0 * M_PI_4) {
		return sin_core(M_PI_2 - x);
	} else if (x <= 5.0 * M_PI_4) {
		return -cos_core(M_PI - x);
	} else if (x <= 7.0 * M_PI_4) {
		return -sin_core(3.0 * M_PI_2 - x);
	} else {
		return cos_core(2.0 * M_PI - x);
	}
}

double sin(double x) {
	if (isnan(x)) return x;
	if (isinf(x)) return NAN;

	x = fmod(x, 2.0 * M_PI);
	if (x <= -M_PI) x += 2.0 * M_PI;
	if (x > M_PI) x -= 2.0 * M_PI;

	if (x < 0) x += 2.0 * M_PI;

	if (x <= M_PI_4) {
		return sin_core(x);
	} else if (x <= 3.0 * M_PI_4) {
		return cos_core(M_PI_2 - x);
	} else if (x <= 5.0 * M_PI_4) {
		return -sin_core(x - M_PI);
	} else if (x <= 7.0 * M_PI_4) {
		return cos_core(x - 3.0 * M_PI_2);
	} else {
		return -sin_core(2.0 * M_PI - x);
	}
}

double tan(double x) {
	return sin(x) / cos(x);
}
