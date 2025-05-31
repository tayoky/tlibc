#include <math.h>

#define PI 3.1415926535f

#define DEG2RAD PI / 180.0f
#define HALF_PI PI * 0.5f
#define TPC 16.0f * (PI - 2.0f * 1.4142135623730950488016887242097f) / (PI * PI * PI)

long double cosl(long double a) {
	float n = fabsl(a) / (2.0f * PI);

	n = (n - ((long double) (int) n)) * PI * 2.0f;
    
	if (n > PI)
		n = PI * 2.0f - n;

	long double res = 0.0f;

	if (n < PI * 0.25f)
		res = 1.0f - 0.48f * n * n;
	else if (n < PI * 0.75f) {
		long double x = n - HALF_PI;
		res = HALF_PI - n + TPC * x * x * x;
	} else {
		n = n - PI;
		res = 0.48f * n * n - 1.0f;
	}

	return res;
}

long double sinl(long double x){
	return cosl(x - PI * 0.5f);
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
