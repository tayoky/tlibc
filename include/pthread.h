#ifndef _PTHREAD_H
#define _PTHREAD_H

#include <sys/types.h>
#include <sys/time.h>
#include <stddef.h>
#include <signal.h>
#include <tlibcnoreturn.h>
#include <sched.h>

#if defined(__STDC_NO_ATOMICS__) || defined(__cplusplus)
// stdatomic in c++ is kind of broken
#define TLIBC_ATOMIC_INT   volatile int
#define TLIBC_ATOMIC_LONG  volatile long
#define TLIBC_ATOMIC_UINT  volatile unsigned int
#define TLIBC_ATOMIC_ULONG volatile unsigned long
#else
#include <stdatomic.h>
#define TLIBC_ATOMIC_INT   atomic_int
#define TLIBC_ATOMIC_LONG  atomic_long
#define TLIBC_ATOMIC_UINT  atomic_uint
#define TLIBC_ATOMIC_ULONG atomic_ulong
#endif

typedef struct __pthread_attr {
	void *stack;
	size_t stack_size;
	size_t guard_size;
	int joinable_state;
	int policy;
	int detach_state;
} pthread_attr_t;

#define PTHREAD_CREATE_JOINABLE 0
#define PTHREAD_CREATE_DETACHED 1

typedef struct __pthread_barrierattr {
	int pshared;
} pthread_barrierattr_t;

typedef struct __pthread_barrier {
	pthread_barrierattr_t attr;
	TLIBC_ATOMIC_ULONG in;
	TLIBC_ATOMIC_ULONG out;
	TLIBC_ATOMIC_ULONG current;
	int initalized;
	unsigned int count;
} pthread_barrier_t;
#define PTHREAD_BARRIER_SERIAL_THREAD 1

typedef struct __pthread_condattr {
	int pshared;
	clockid_t clock_id;
} pthread_condattr_t;

typedef struct __pthread_cond {
	pthread_condattr_t attr;
	TLIBC_ATOMIC_ULONG seq;
	int initalized;
} pthread_cond_t;
#define PTHREAD_COND_INITIALIZER {{0, CLOCK_MONOTONIC}, 0, 1}

typedef struct __pthread_mutexattr {
	int pshared;
	int type;
	int protocol;
} pthread_mutexattr_t;

#define PTHREAD_PRIO_NONE    0
#define PTHREAD_PRIO_INHERIT 1
#define PTHREAD_PRIO_PROTECT 2

#define PTHREAD_MUTEX_DEFAULT    0
#define PTHREAD_MUTEX_NORMAL     1
#define PTHREAD_MUTEX_ERRORCHECK 2
#define PTHREAD_MUTEX_RECURSIVE  3

typedef struct __pthread_mutex {
	pthread_mutexattr_t attr;
	size_t lock_count;
	TLIBC_ATOMIC_LONG lock;
} pthread_mutex_t;
#define PTHREAD_MUTEX_INITIALIZER {\
	.attr = {\
		.pshared  = PTHREAD_PROCESS_PRIVATE,\
		.type     = PTHREAD_MUTEX_DEFAULT,\
		.protocol = PTHREAD_PRIO_NONE,\
	},\
	.lock_count = 0,\
	.lock = 0,\
}

typedef struct __pthread_rwlockattr {
	int pshared;
} pthread_rwlockattr_t;

typedef struct __pthread_rwlock {
	pthread_rwlockattr_t attr;
	TLIBC_ATOMIC_LONG lock;
	int initalized;
} pthread_rwlock_t;

typedef TLIBC_ATOMIC_INT pthread_once_t;
#define PTHREAD_ONCE_INIT 0

typedef TLIBC_ATOMIC_INT pthread_spinlock_t;

struct __uthread;
typedef struct __uthread *pthread_t;

typedef unsigned int pthread_key_t;

#define PTHREAD_PROCESS_PRIVATE 0
#define PTHREAD_PROCESS_SHARED  1

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
int pthread_join(pthread_t thread, void **arg);
TLIBC_NORETURN void pthread_exit(void *retval);
int pthread_equal(pthread_t t1, pthread_t t2);
pthread_t pthread_self(void);
int pthread_once(pthread_once_t *once_control, void (*init_routine)(void));
int pthread_detach(pthread_t thread);
int pthread_cancel(pthread_t thread);
int pthread_setname_np(pthread_t thread, const char *name);
int pthread_getname_np(pthread_t thread, char *name, size_t size);
int pthread_getschedparam(pthread_t thread, int *restrict policy, struct sched_param *restrict param);
int pthread_setschedparam(pthread_t thread, int policy, const struct sched_param *param);

int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
int pthread_attr_getstacksize(const pthread_attr_t *restrict attr, size_t *restrict stacksize);
int pthread_attr_setstack(pthread_attr_t *attr, void *stackaddr, size_t stacksize);
int pthread_attr_getstack(const pthread_attr_t *restrict attr, void **restrict stackaddr, size_t *restrict stacksize);
int pthread_attr_setguardsize(pthread_attr_t *attr, size_t guardsize);
int pthread_attr_getguardsize(const pthread_attr_t *restrict attr, size_t *restrict guardsize);
int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
int pthread_attr_getdetachstate(const pthread_attr_t *restrict attr, int *restrict detachstate);

int pthread_barrier_init(pthread_barrier_t *restrict barrier, const pthread_barrierattr_t *restrict attr, unsigned int count);
int pthread_barrier_destroy(pthread_barrier_t *barrier);
int pthread_barrier_wait(pthread_barrier_t *barrier);

int pthread_barrierattr_init(pthread_barrierattr_t *barrierattr);
int pthread_barrierattr_destroy(pthread_barrierattr_t *barrierattr);
int pthread_barrierattr_getpshared(const pthread_barrierattr_t *restrict barrierattr, int *restrict pshared);
int pthread_barrierattr_setpshared(pthread_barrierattr_t *barrierattr, int pshared);

int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
int pthread_cond_destroy(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime);
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);

int pthread_condattr_init(pthread_condattr_t *condattr);
int pthread_condattr_destroy(pthread_condattr_t *condattr);
int pthread_condattr_getpshared(const pthread_condattr_t *restrict condattr, int *restrict pshared);
int pthread_condattr_setpshared(pthread_condattr_t *condattr, int pshared);
int pthread_condattr_getclock(const pthread_condattr_t *restrict condattr, clockid_t *restrict clock_id);
int pthread_condattr_setclock(pthread_condattr_t *condattr, clockid_t clock_id);

int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict mutexattr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
// int pthread_mutex_getprioceiling(const pthread_mutex_t *restrict, int *restrict);
// int pthread_mutex_setprioceiling(pthread_mutex_t *restrict mutex, int, int *restrict);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_timedlock(pthread_mutex_t *restrict mutex, const struct timespec *restrict timeout);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);

int pthread_mutexattr_init(pthread_mutexattr_t *mutexattr);
int pthread_mutexattr_destroy(pthread_mutexattr_t *mutexattr);
// int pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *restrict mutexattr, int *);
// int pthread_mutexattr_setprioceiling(pthread_mutexattr_t *mutexattr, int);
int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *restrict mutexattr, int *restrict protocol);
int pthread_mutexattr_setprotocol(pthread_mutexattr_t *mutexattr, int protocol);
int pthread_mutexattr_getpshared(const pthread_mutexattr_t *restrict mutexattr, int *restrict pshared);
int pthread_mutexattr_setpshared(pthread_mutexattr_t *mutexattr, int pshared);
int pthread_mutexattr_gettype(const pthread_mutexattr_t *restrict mutexattr, int *restrict type);
int pthread_mutexattr_settype(pthread_mutexattr_t *mutexattr, int type);

int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr);
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);

int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_timedrdlock(pthread_rwlock_t *restrict rwlock, const struct timespec *restrict timeout);
int pthread_rwlock_timedwrlock(pthread_rwlock_t *restrict rwlock, const struct timespec *restrict timeout);
int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);

int pthread_rwlockattr_init(pthread_rwlockattr_t *attr);
int pthread_rwlockattr_destroy(pthread_rwlockattr_t *attr);
int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *attr, int pshared);
int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *restrict attr, int *restrict pshared);

int pthread_key_create(pthread_key_t *key, void (*)(void *));
int pthread_key_delete(pthread_key_t key);
int pthread_setspecific(pthread_key_t key, const void *value);
void *pthread_getspecific(pthread_key_t key);

int pthread_spin_init(pthread_spinlock_t *lock, int pshared);
int pthread_spin_destroy(pthread_spinlock_t *lock);
int pthread_spin_lock(pthread_spinlock_t *lock);
int pthread_spin_trylock(pthread_spinlock_t *lock);
int pthread_spin_unlock(pthread_spinlock_t *lock);

#endif
