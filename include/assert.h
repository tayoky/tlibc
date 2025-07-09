#ifndef ASSERT_H
#define ASSERT_H

#ifdef NDEBUG
#define assert(cond)
#else
void __assert(const char *expr,const char *file,long line,const char *func);
#define assert(cond) ((cond) ? (void)(0) : __assert(#cond,__FILE__,__LINE__,__func__))
#endif


#endif