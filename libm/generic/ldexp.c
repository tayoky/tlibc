#include <math.h>
#include <errno.h>
#include "internal.h"

#define template(type,itype,name,shift,max,huge) type name(type a, int exp) {\
	if(exp > (max) || exp < -(max + 1)){\
		errno = ERANGE;\
		return huge;\
	}\
	itype power = ((itype)(exp + max) << (shift));\
	return a * (*(type*) &power);\
}

template(float,intflt_t,ldexpf,FLT_MANT_DIG-1,FLT_MAX_EXP-1,HUGE_VALF)
template(double,intdbl_t,ldexp,DBL_MANT_DIG-1,DBL_MAX_EXP-1,HUGE_VAL)
