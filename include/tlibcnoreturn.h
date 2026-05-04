#ifndef _TLIBC_NORETURN_H
#define _TLIBC_NORETURN_H

// we need noreturn (even in c99)
#ifdef __GNUC__
#define TLIBC_NORETURN __attribute__((noreturn))
#else
#define TLIBC_NORETURN
#endif

#endif
