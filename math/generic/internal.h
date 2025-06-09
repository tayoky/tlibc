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
#else
//#error unsupported long double size
bits(ldbl,64)
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

#endif
