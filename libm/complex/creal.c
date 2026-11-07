#include <complex.h>

double creal(double complex z) {
	return __real__ z;
}
