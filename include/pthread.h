#ifndef _PTHREAD_H
#define _PTHREAD_H

#include <sys/types.h>

#ifdef __STDC_NO_ATOMICS__
//we are cooked
#error "no atomic functions"
#else
#include <stdatomic.h>
#endif

typedef pid_t pthread_t;
typedef atomic_flag pthread_once_t;

#define PTHREAD_ONCE_INIT ATOMIC_FLAG_INIT

//idk
typedef int pthread_attr_t;

int pthread_create(pthread_t *thread,const pthread_attr_t *attr,void *(*start_routine)(void *),void *arg);
void pthread_exit(void *retval);
int pthread_equal(pthread_t t1, pthread_t t2);
pthread_t pthread_self(void);
int pthread_once(pthread_once_t *once_control, void (*init_routine)(void));

#endif