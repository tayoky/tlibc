#ifndef _SETJMP_H
#define _SETJMP_H

#include <stdint.h>
#include <signal.h>

#ifdef x86_64
typedef uint64_t jmp_buf[8];
#elif defined(__aarch64__)
typedef uint64_t jmp_buf[14];
#else
typedef uintptr_t jmp_buf[8];
#endif

struct __sigjmp_buf {
	jmp_buf buf;
	sigset_t mask;
	int savemask;
};
typedef struct __sigjmp_buf sigjmp_buf[1];

int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int value);
int sigsetjmp(sigjmp_buf env, int savemask);
void siglongjmp(sigjmp_buf env, int value);

#endif
