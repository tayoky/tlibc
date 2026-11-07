#include <complex.h>

float cimagf(float complex z) {
	return __imag__ z;
}
