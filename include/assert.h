#ifndef _ASSERT_H
#define _ASSERT_H

void __assert(const char *expr,const char *file,long line,const char *func);

#if !defined(__cplusplus) && __STDC_VERSION__ < 202311L
#if __STDC_VERSION__ >= 201112L
#define static_assert _Static_assert
#else
#define static_assert(cond, msg) static char _static_assert_ ## __LINE__[((cond) && (msg)) - 1];
#endif
#endif

#endif

#undef assert
#ifdef NDEBUG
#define assert(cond) ((void)0)
#else
#define assert(cond) ((cond) ? (void)(0) : __assert(#cond,__FILE__,__LINE__,__func__))
#endif
