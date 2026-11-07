#ifndef _COMPLEX_H
#define _COMPLEX_H

#include <features.h>

#define complex _Complex
#define _Complex_I ((float _Complex){0.0f, 1.0f})
#define I _Complex_I

double creal(double complex z);
float crealf(float complex z);
long double creall(long double complex z);

#endif
