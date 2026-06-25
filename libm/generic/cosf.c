#include <math.h>

// constants taken from FreeBSD
static const float c[] = {
	4.16666666666666019037e-02f,
	-1.38888888888741095749e-03f,
	2.48015872894767294178e-05f,
	-2.75573143513906633035e-07f,
	2.08757232129817482790e-09f,
	-1.13596475577381996161e-11f,
};

static float cos_core(float x) {
	float x2 = x * x;
	float x4 = x2 * x2;

	// minimax polyminal using Horner's Method
	float res = c[5];
	for (int i = 4; i >= 0; i--) {
		res = res * x2 + c[i];
	}
	res *= x4;
	return 1.0 - x2 / 2.0 + res;
}

// constants taken from FreeBSD
static const float s[] = {
	-1.66666666666666324348e-01f,
	8.33333333332248946124e-03f,
	-1.98412698298579493134e-04f,
	2.75573137070700676789e-06f,
	-2.50507602534068634195e-08f,
	1.58969099521155010221e-10f,
};

static float sin_core(float x) {
	float x2 = x * x;
	float x3 = x2 * x;

	// minimax polyminal using Horner's Method
	float res = s[5];
	for (int i = 4; i >= 0; i--) {
		res = res * x2 + s[i];
	}
	return x + x3 * res;
}


float cosf(float x) {
	if (isnan(x)) return x;
	if (isinf(x)) return NAN;

	x = fmodf(x + M_PI, 2.0f * M_PI);
	if (x < 0) x += 2.0f * M_PI;
	x -= M_PI;

	if (x < -3.0f * M_PI_4) {
		return -cos_core(M_PI + x);
	} else if (x < -M_PI_4) {
		return -sin_core(-M_PI_2 - x);
	} else if (x <= M_PI_4) {
		return cos_core(x);
	} else if (x <= 3.0f * M_PI_4) {
		return -sin_core(M_PI_2 - x);
	} else {
		return -cos_core(M_PI - x);
	}
}

float sinf(float x) {
	if (isnan(x)) return x;
	if (isinf(x)) return NAN;

	x = fmodf(x + M_PI, 2.0f * M_PI);
	if (x < 0) x += 2.0f * M_PI;
	x -= M_PI;

	if (x < -3.0f * M_PI_4) {
		return -cos_core(M_PI + x);
	} else if (x < -M_PI_4) {
		return -sin_core(-M_PI_2 - x);
	} else if (x <= M_PI_4) {
		return sin_core(x);
	} else if (x <= 3.0f * M_PI_4) {
		return cos_core(M_PI_2 - x);
	} else {
		return sin_core(M_PI - x);
	}
}
