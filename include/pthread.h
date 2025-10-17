#ifndef _PTHREAD_H
#define _PTHREAD_H

#include <sys/types.h>
#include <stddef.h>
#include <stdnoreturn.h>

#ifdef __STDC_NO_ATOMICS__
//we are cooked
#error "no atomic functions"
#else
#include <stdatomic.h>
#endif

typedef pid_t pthread_t;
typedef atomic_flag pthread_once_t;
typedef struct __pthread_attr {
    void *stack;
    size_t stack_size;
    size_t guard_size;
    int joinable_state;
    int policy;
} pthread_attr_t;

#define PTHREAD_ONCE_INIT ATOMIC_FLAG_INIT


int pthread_create(pthread_t *thread,const pthread_attr_t *attr,void *(*start_routine)(void *),void *arg);
void noreturn pthread_exit(void *retval);
int pthread_equal(pthread_t t1, pthread_t t2);
pthread_t pthread_self(void);
int pthread_once(pthread_once_t *once_control, void (*init_routine)(void));
int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
int pthread_attr_getstacksize(const pthread_attr_t *restrict attr,size_t *restrict stacksize);
int pthread_attr_setstack(pthread_attr_t *attr,void *stackaddr,size_t stacksize);
int pthread_attr_getstack(const pthread_attr_t *restrict attr,void **restrict stackaddr,size_t *restrict stacksize);
int pthread_attr_setguardsize(pthread_attr_t *attr, size_t guardsize);
int pthread_attr_getguardsize(const pthread_attr_t *restrict attr,size_t *restrict guardsize);

#endif