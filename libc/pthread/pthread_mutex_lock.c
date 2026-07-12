#include <sysdeps.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

int pthread_mutex_lock(pthread_mutex_t *mutex) {
	if (!mutex) return EINVAL;
	for (;;) {
		futex_val_t expected = 0;
		if (atomic_compare_exchange_strong(&mutex->lock, &expected, (futex_val_t)gettid())) {
			// we acquired the lock !
			mutex->lock_count = 1;
			return 0;
		}
		// maybee we already own it
		if (expected == (futex_val_t)gettid()) {
			switch (mutex->attr.type) {
			case PTHREAD_MUTEX_RECURSIVE:
				mutex->lock_count++;
				return 0;
			case PTHREAD_MUTEX_ERRORCHECK:
				return EDEADLK;
			}
			// we are going to deadlock
			// this is intended behaviour
		}
		if (sys_futex_wait(&mutex->lock, expected) < 0 && errno != EAGAIN) return errno;
	}
}
