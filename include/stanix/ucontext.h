#ifndef _UCONTEXT
#define _UCONTEXT

#include <sys/signal.h>
#include <stdint.h>

typedef uintptr_t mcontext_t[32];
typedef struct __ucontext {
    struct __ucontext *uc_link;
    sigset_t    uc_sigmask;
    stack_t     uc_stack;
    mcontext_t  uc_mcontext;
} ucontext_t;


#endif