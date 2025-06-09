#include <math.h>
#include <float.h>
#include "internal.h"

#define template(type,name,itype,m_size,m_mask,e_mask) type log2##name(type n) {\
    if (n <= 0.0f) return -INFINITY;\
\
    itype E, M;\
\
    M = (*(itype *) &n) & (m_mask);\
    E = ((*(itype *) &n) >> (m_size)) & (e_mask);\
\
    return ((type) E) - 127.0f + log##name##2_01(M / 8388608.0f);\
}
template(float,f,uintflt_t,FLT_MANT_DIG-1,FLT_MANT_MASK,FLT_EXP_MASK)
template(double,,uintdbl_t,DBL_MANT_DIG-1,DBL_MANT_MASK,DBL_EXP_MASK)
template(long double,l,uintldbl_t,LDBL_MANT_DIG-1,LDBL_MANT_MASK,LDBL_EXP_MASK)

