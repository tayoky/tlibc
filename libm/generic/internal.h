#ifndef _INTERNAL_H
#define _INTERNAL_H

#include <float.h>
#include <limits.h>
#include <stdint.h>

#define __mask(suffix, bits) (((1 ## suffix) << (bits)) - 1 ## suffix)

#define FLT_MANT_BITS  (FLT_MANT_DIG-1)
#define DBL_MANT_BITS  (DBL_MANT_DIG-1)
#define LDBL_MANT_BITS (LDBL_MANT_DIG-1)

#define FLT_MANT_MASK  __mask(UL,FLT_MANT_BITS)
#define DBL_MANT_MASK  __mask(UL,DBL_MANT_BITS)
#define LDBL_MANT_MASK __mask(ULL,LDBL_MANT_BITS)
#define FLT_EXP_MASK  __mask(UL,sizeof(float)*CHAR_BIT-FLT_MANT_DIG)
#define DBL_EXP_MASK  __mask(UL,sizeof(double)*CHAR_BIT-DBL_MANT_DIG)
#define LDBL_EXP_MASK __mask(ULM,sizeof(long double)*CHAR_BIT-LDBL_MANT_DIG)

// TODO : figure out these
#define FLT_EXP_HALF  0x7eUL
#define DBL_EXP_HALF  0x3feUL
#define LDBL_EXP_HALF 0x0
#define FLT_SIGN_BIT  31
#define DBL_SIGN_BIT  63
#define LDBL_SIGN_BIT 0
#define FLT_SIGN_MASK  (1UL << FLT_SIGN_BIT)
#define DBL_SIGN_MASK  (1UL << DBL_SIGN_BIT)
#define LDBL_SIGN_MASK (1UL << LDBL_SIGN_BIT)

typedef uint32_t uintflt_t;
typedef uint64_t uintdbl_t;
typedef uint64_t uintldbl_t;

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
