#ifndef _INTERNAL_H
#define _INTERNAL_H

#include <float.h>
#include <limits.h>
#include <stdint.h>

#define bits(name,bit) \
	typedef int##bit##_t  int##name##_t;\
	typedef uint##bit##_t uint##name##_t;

#if __SIZEOF_FLOAT__ == 2
bits(flt,16)
#elif __SIZEOF_FLOAT__ == 4
bits(flt,32)
#elif __SIZEOF_FLOAT__ == 8
bits(flt,64)
#else
#error unsupported float size
#endif

#if __SIZEOF_DOUBLE__ == 2
bits(dbl,16)
#elif __SIZEOF_DOUBLE__ == 4
bits(dbl,32)
#elif __SIZEOF_DOUBLE__ == 8
bits(dbl,64)
#else
#error unsupported double size
#endif

#if __SIZEOF_LONG_DOUBLE__ == 2
bits(ldbl,16)
#elif __SIZEOF_LONG_DOUBLE__ == 4
bits(ldbl,32)
#elif __SIZEOF_LONG_DOUBLE__ == 8
bits(ldbl,64)
#elif __SIZEOF_LONG_DOUBLE__ == 16 && defined(__SIZEOF_INT128__)
//modern compiler have a built in __int128_t
typedef __int128_t  intldbl_t;
typedef __uint128_t uintldbl_t;
#else
#error unsupported long double size
#endif

#undef bit

#define __mask(type,bits) (((type)-1)&~(((type)1 << (sizeof(type)*CHAR_BIT-1))) >> (sizeof(type)*CHAR_BIT-(bits)-1))

#define FLT_MANT_MASK __mask(uintflt_t,FLT_MANT_DIG-1)
#define DBL_MANT_MASK __mask(uintdbl_t,DBL_MANT_DIG-1)
#define LDBL_MANT_MASK __mask(uintldbl_t,LDBL_MANT_DIG-1)
#define FLT_EXP_MASK __mask(uintflt_t,sizeof(uintflt_t)*CHAR_BIT-FLT_MANT_DIG)
#define DBL_EXP_MASK __mask(uintdbl_t,sizeof(uintdbl_t)*CHAR_BIT-DBL_MANT_DIG)
#define LDBL_EXP_MASK __mask(uintldbl_t,sizeof(uintldbl_t)*CHAR_BIT-LDBL_MANT_DIG)

#define template(type,name) static inline type log##name##2_01(type x) {\
    type x2 = x * x, x3 = x2 * x, x4 = x3 * x, x5 = x4 * x;\
\
    return 0.0426634327651f * x5 - 0.1860397355647f * x4 + 0.4075559395645f * x3 - 0.7055868559292f * x2 + 1.4414072191643f * x;\
}\
static inline type pow##name##2_01(type x) {\
    type x2 = x * x, x3 = x2 * x, x4 = x3 * x, x5 = x4 * x;\
\
    return 0.0018932135149f * x5 + 0.0089454792171f * x4 + 0.0558701110667f * x3 + 0.2401360232927f * x2 + 0.6931551729086f * x + 1.0f;\
}

template(float,f)
template(double,)
template(long double,l)

#undef template

// check for builtin
#if defined(__GNUC__) || defined(__clang__)
#define HAVE_BUILTIN_COS  1
#define HAVE_BUILTIN_COSF 1
#define HAVE_BUILTIN_COSL 1
#define HAVE_BUILTIN_SIN 1
#define HAVE_BUILTIN_SINF 1
#define HAVE_BUILTIN_SINL 1
#define HAVE_BUILTIN_TAN 1
#define HAVE_BUILTIN_TANF 1
#define HAVE_BUILTIN_TANL 1
#define HAVE_BUILTIN_ACOS 1
#define HAVE_BUILTIN_ACOSF 1
#define HAVE_BUILTIN_ACOSL 1
#define HAVE_BUILTIN_ASIN 1
#define HAVE_BUILTIN_ASINF 1
#define HAVE_BUILTIN_ASINL 1
#define HAVE_BUILTIN_ATAN 1
#define HAVE_BUILTIN_ATANF 1
#define HAVE_BUILTIN_ATANL 1
#define HAVE_BUILTIN_ATAN2 1
#define HAVE_BUILTIN_ATAN2F 1
#define HAVE_BUILTIN_ATAN2L 1
#define HAVE_BUILTIN_POW 1
#define HAVE_BUILTIN_POWF 1
#define HAVE_BUILTIN_POWL 1
#endif

#endif
