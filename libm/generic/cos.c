#include <math.h>

#define DEG2RAD PI / 180.0f
#define TPC 16.0f * (M_PI - 2.0f * 1.4142135623730950488016887242097f) / (M_PI * M_PI * M_PI)

long double cosl(long double a) {
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
}

long double sinl(long double x){
	return cosl(x - M_PI_2);
}

double cos(double x){
	return (double)cosl((long double)x);
}

double sin(double x){
	return (double)sinl((long double)x);
}

float cosf(float x){
	return (float)cosl((long double)x);
}

float sinf(float x){
	return (float)sinl((long double)x);
}
