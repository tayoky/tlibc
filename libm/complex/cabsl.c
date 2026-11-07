#include <complex.h>
#include <math.h>

long double cabsl(long double complex z) {
	long double real = creall(z);
	long double imag = cimagl(z);
	return sqrtl(real * real + imag * imag);
}
