#ifndef _CDEFS_H
#define _CDEFS_H

#ifdef __cpluscplus
#define _BEGIN_C_HEADER extern "C" {
#define _END_C_HEADER   }
// c++ does not have the restrict keywrod
#ifdef __GNUC__
#define restrict __restrict
#else
#define restrict
#endif
#else
#define _BEGIN_C_HEADER
#define _END_C_HEADER
#endif

#endif
