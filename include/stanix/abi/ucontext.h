#ifndef _ABI_UCONTEXT_H
#define _ABI_UCONTEXT_H

// Stanix ucontext ABI

#include <sys/signal.h>
#include <stdint.h>

typedef uintptr_t mcontext_t[96];
typedef struct __ucontext {
    struct __ucontext *uc_link;
    sigset_t    uc_sigmask;
    stack_t     uc_stack;
    mcontext_t  uc_mcontext;
} ucontext_t;

#endif
