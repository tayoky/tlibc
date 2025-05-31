#ifndef MATH_H
#define MATH_H

#define ifunc(name) int name(int x);\
	long l##name(long x);\
	long long ll##name(long long x);
#define ffunc(name) float name##f(float x);\
	double name(double x);\
	long double name##l(long double x);

//abs
ffunc(fabs)

ffunc(cos)
ffunc(sin)
ffunc(tan)

ffunc(fmin)
ffunc(fmax)

ffunc(sqrt)

#undef ifunc
#undef ffunc

//constant

#define M_PI 3.1415926535f
#define M_PI_2 (M_PI * 0.5f)
#define M_PI_4 (M_PI * 0.25f)
#define M_1_PI (1.0f / M_PI)
#define M_2_PI (2.0f / M_PI)

#endif
