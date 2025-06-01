#ifndef SETJMP_H
#define SETJMP_H

#include <stdint.h>

#ifdef x86_64
typedef uint64_t jmp_buf[7];
#elif defined(__aarch64__)
typedef uint64_t jmp_buf[13];
#else
typedef uintptr_t jmp_buf[8];
#endif

int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int value);

#endif
