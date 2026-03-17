#include <math.h>

float tanf(float x) {
	return sinf(x) / cosf(x);
}

double tan(double x) {
	return sin(x) / cos(x);
}

long double tanl(long double x) {
	return sinl(x) / cosl(x);
}
