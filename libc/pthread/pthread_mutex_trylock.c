#include <sysdeps.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

int pthread_mutex_trylock(pthread_mutex_t *mutex) {
	if (!mutex) return EINVAL;
	futex_val_t expected = 0;
	if (atomic_compare_exchange_strong(&mutex->lock, &expected, (futex_val_t)gettid())) {
		// we acquired the lock !
		mutex->lock_count = 1;
		return 0;
	}
	// maybee we already own it
	if (mutex->attr.type == PTHREAD_MUTEX_RECURSIVE && expected == (futex_val_t)gettid()) {
		mutex->lock_count++;
		return 0;
	}
	return EBUSY;
}
