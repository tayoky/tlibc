#include <complex.h>
#include <math.h>

double cabs(double complex z) {
	double real = creal(z);
	double imag = cimag(z);
	return sqrt(real * real + imag * imag);
}
