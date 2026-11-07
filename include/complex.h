#ifndef _COMPLEX_H
#define _COMPLEX_H

#include <features.h>

#define complex _Complex
#define _Complex_I ((float _Complex){0.0f, 1.0f})
#define I _Complex_I

double cabs(double complex z);
float cabsf(float complex z);
long double cabsl(long double complex z);

double carg(double complex z);
float cargf(float complex z);
long double cargl(long double complex z);

double cimag(double complex z);
float cimagf(float complex z);
long double cimagl(long double complex z);

double creal(double complex z);
float crealf(float complex z);
long double creall(long double complex z);

#endif
