#ifndef MATH_H
#define MATH_H

#define ifunc(name) int name(int x);\
	long l##name(long x);\
	long long ll##name(long long x);
#define ffunc(name) float name##f(float x);\
	double name(double x);\
	long double name##l(long double x);

//abs
ifunc(abs)
ffunc(fabs)

ffunc(cos)
ffunc(sin)

ffunc(sqrt)

#undef ifunc
#undef ffunc



#endif
