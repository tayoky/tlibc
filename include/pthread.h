#ifndef _PTHREAD_H
#define _PTHREAD_H

#include <sys/types.h>
#include <sys/time.h>
#include <stddef.h>
#include <stdnoreturn.h>

#ifdef __STDC_NO_ATOMICS__
//we are cooked
#error "no atomic functions"
#else
#include <stdatomic.h>
#endif

typedef struct __pthread_attr {
    void *stack;
    size_t stack_size;
    size_t guard_size;
    int joinable_state;
    int policy;
} pthread_attr_t;

typedef struct __pthread_condattr {
	int pshared;
	clockid_t clock_id;
} pthread_condattr_t;

typedef struct __pthread_cond {
	pthread_condattr_t attr;
} pthread_cond_t;
#define PTHREAD_COND_INITALIZER {{0, CLOCK_MONOTONIC}}

typedef struct __pthread_mutexattr {
	int pshared;
} pthread_mutexattr_t;

typedef struct __pthread_mutex {
	pthread_mutexattr_t attr;
} pthread_mutex_t;

typedef atomic_flag pthread_once_t;
#define PTHREAD_ONCE_INIT ATOMIC_FLAG_INIT

typedef atomic_flag pthread_spinlock_t;
typedef pid_t pthread_t;


#define PTHREAD_PROCESS_PRIVATE 0
#define PTHREAD_PROCESS_SHARED  1

int pthread_create(pthread_t *thread,const pthread_attr_t *attr,void *(*start_routine)(void *),void *arg);
int pthread_join(pthread_t thread, void **arg);
noreturn void pthread_exit(void *retval);
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

/*
 * TODO : implement these
 * int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
 * int pthread_cond_destroy(pthread_cond_t *cond);
 * int pthread_cond_broadcast(pthread_cond_t *cond);
 * int pthread_cond_signal(pthread_cond_t *cond);
 * int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime);
 * int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
 */

int pthread_condattr_init(pthread_condattr_t *condattr);
int pthread_condattr_destroy(pthread_condattr_t *condattr);
int pthread_condattr_getpshared(const pthread_condattr_t *condattr, int *pshared);
int pthread_condattr_setpshared(pthread_condattr_t *condattr, int pshared);
int pthread_condattr_getclock(const pthread_condattr_t *condattr, clockid_t *clock_id);
int pthread_condattr_setclock(pthread_condattr_t *condattr, clockid_t clock_id);

int pthread_spin_init(pthread_spinlock_t *lock, int pshared);
int pthread_spin_destroy(pthread_spinlock_t *lock);
int pthread_spin_lock(pthread_spinlock_t *lock);
int pthread_spin_trylock(pthread_spinlock_t *lock);
int pthread_spin_unlock(pthread_spinlock_t *lock);

#endif
