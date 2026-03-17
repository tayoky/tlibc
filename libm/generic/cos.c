#include <math.h>

#define DEG2RAD PI / 180.0f
#define TPC 16.0f * (M_PI - 2.0f * 1.4142135623730950488016887242097f) / (M_PI * M_PI * M_PI)

long double cosl(long double a) {
#ifdef HAVE_BUILTIN_COSL
	return __builtin_cosl(a);
#else
	float n = fabsl(a) / (2.0f * M_PI);

	n = (n - ((long double) (int) n)) * M_PI * 2.0f;
    
	if (n > M_PI)
		n = M_PI * 2.0f - n;

	long double res = 0.0f;

	if (n < M_PI * 0.25f)
		res = 1.0f - 0.48f * n * n;
	else if (n < M_PI * 0.75f) {
		long double x = n - M_PI_2;
		res = M_PI_2 - n + TPC * x * x * x;
	} else {
		n = n - M_PI;
		res = 0.48f * n * n - 1.0f;
	}

	return res;
#endif
}

long double sinl(long double x){
#ifdef HAVE_BUILTIN_SINL
	return __builtin_sinl(x);
#else
	return cosl(x - M_PI_2);
#endif
}

double cos(double x){
#ifdef HAVE_BUILTIN_COS
	return __builtin_cos(x);
#else
	return (double)cosl((long double)x);
#endif
}

double sin(double x){
#ifdef HAVE_BUILTIN_SIN
	return __builtin_sin(x);
#else
	return (double)sinl((long double)x);
#endif
}

float cosf(float x){
#ifdef HAVE_BUILTIN_COSF
	return __builtin_cosf(x);
#else
	return (float)cosl((long double)x);
#endif
}

float sinf(float x){
#ifdef HAVE_BUILTIN_SINF
	return __builtin_sinf(x);
#else
	return (float)sinl((long double)x);
#endif
}
