#include <complex.h>
#include <math.h>

float cabsf(float complex z) {
	float real = crealf(z);
	float imag = cimagf(z);
	return sqrtf(real * real + imag * imag);
}
