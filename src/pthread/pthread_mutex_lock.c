#include <sys/futex.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

int pthread_mutex_lock(pthread_mutex_t *mutex) {
	if (!mutex) return EINVAL;
	for (;;) {
		pid_t expected = 0;
		if (atomic_compare_exchange_strong(&mutex->lock, &expected, gettid())) {
			// we acquired the lock !
			mutex->lock_count = 1;
			return 0;
		}
		// maybee we already own it
		if (expected == gettid()) {
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
		futex((pid_t*)&mutex->lock, FUTEX_WAIT, expected); 
	}
}
