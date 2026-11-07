#include <complex.h>

double cimag(double complex z) {
	return __imag__ z;
}
