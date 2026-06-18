#ifndef _ASSERT_H
#define _ASSERT_H

void __assert(const char *expr,const char *file,long line,const char *func);

#endif

#undef assert
#ifdef NDEBUG
#define assert(cond) ((void)0)
#else
#define assert(cond) ((cond) ? (void)(0) : __assert(#cond,__FILE__,__LINE__,__func__))
#endif
