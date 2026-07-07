#ifndef _MATH_H
#define _MATH_H

#include <limits.h>
#include <float.h>

typedef float float_t;
typedef double double_t;

//macro

// on GCC we can use builtins
#define fpclassify(x) __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL, FP_SUBNORMAL, FP_ZERO, x)
#define FP_NAN       0
#define FP_INFINITE  1
#define FP_NORMAL    2
#define FP_SUBNORMAL 3
#define FP_ZERO      4

// builtin are only faster on GCC
#if defined(__GNUC__) && !defined(__clang__)
#define signbit(x) __builtin_signbit(x)
#define isgreater(x,y) __builtin_isgreater(x,y)
#define isgreaterequal(x,y) __builtin_isgreaterequal(x,y)
#define isless(x,y) __builtin_isless(x,y)
#define islessequal(x,y) __builtin_islessequal(x,y)
#define islessgreater(x,y) __builtin_islessgreater(x,y)
#define isfinite(x) __builtin_isfinite(x)
#define isinf(x) __builtin_isinf_sign(x)
#define isnan(x) __builtin_isnan(x)
#define isnormal(x) __builtin_isnormal(x)
#else
#define signbit(x) (x < 0)
#define func(x,y,op) (isunordered(x,y) ? NAN : (op))
#define isgreater(x,y) func(x,y,x > y)
#define isgreaterequal(x,y) func(x,y,x >= y)
#define isless(x,y) func(x,y,x < y)
#define islessequal(x,y) func(x,y,x <= y)
#define islessgreater(x,y) func(x,y,x != y)
#define isfinite(x) (fpclassify(x) != FP_INFINITE)
#define isinf(x)    (fpclassify(x) == FP_INFINITE)
#define isnan(x)    (fpclassify(x) == FP_NAN)
#define isnormal(x) (fpclassify(x) == FP_NORMAL)
#undef func
#endif

#define isunordered(x,y) (isnan(x) || isnan(y))

#define ifunc(type, name) type name##f(float x);\
	type name(double x);\
	type name##l(long double x);
#define ffunc(name) float name##f(float x);\
	double name(double x);\
	long double name##l(long double x);
#define ffunc2(name) float name##f(float x,float y);\
	double name(double x,double y);\
	long double name##l(long double x,long double y);

//abs
ffunc(fabs)

ffunc(cos)
ffunc(sin)
ffunc(tan)
void sincosf(float x, float *sin, float *cos);
void sincos(double x, double *sin, double *cos);
void sincosl(long double x, long double *sin, long double *cos);
ffunc(acos)
ffunc(asin)
ffunc(atan)
ffunc2(atan2)
ffunc(cosh)
ffunc(sinh)
ffunc(tanh)
ffunc2(hypot)

ffunc2(fmin)
ffunc2(fmax)
ffunc2(fmod)
ffunc2(copysign)

ffunc(trunc)
ffunc(floor)
ffunc(ceil)
ffunc(round)
ifunc(long, lround)
ifunc(long long, llround)
ffunc(rint)
ifunc(long, lrint)
ifunc(long long, llrint)

ffunc(sqrt)
ffunc(erf)

ffunc(log)
ffunc(log2)
ffunc(log10)

ffunc(exp)
ffunc(exp2)

float ldexpf(float a, int exp);
double ldexp(double a, int exp);
long double ldexpl(long double a, int exp);

double frexp(double num, int *exp);
float frexpf(float num, int *exp);
long double frexpl(long double num, int *exp);

double modf(double x, double *iptr);
float modff(float value, float *iptr);
long double modfl(long double value, long double *iptr);

double fma(double x, double y, double z);
float fmaf(float x, float y, float z);
long double fmal(long double x, long double y, long double z);

ffunc2(pow)
ffunc(exp)

#undef ifunc
#undef ffunc
#undef ffunc2

// constants

#define M_E             2.7182818284590452354
#define M_LOG2E         1.4426950408889634074
#define M_LOG10E        0.43429448190325182765
#define M_LN2           0.69314718055994530942
#define M_LN10          2.30258509299404568402
#define M_PI            3.14159265358979323846
#define M_PI_2          1.57079632679489661923
#define M_PI_4          0.78539816339744830962
#define M_1_PI          0.31830988618379067154
#define M_2_PI          0.63661977236758134308
#define M_2_SQRTPI      1.12837916709551257390
#define M_SQRT2         1.41421356237309504880
#define M_SQRT1_2       0.70710678118654752440

#ifndef NAN
#define NAN __builtin_nanf("")
#endif
#ifndef INFINITY
#define INFINITY __builtin_inff()
#endif
#define HUGE_VALF __builtin_huge_valf()
#define HUGE_VAL  __builtin_huge_val()
#define HUGE_VALL __builtin_huge_vall()

#endif
