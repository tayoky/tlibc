#include <pthread.h>
#include <unistd.h>
#include <errno.h>

int pthread_mutex_trylock(pthread_mutex_t *mutex) {
	if (!mutex) return EINVAL;
	pid_t expected = 0;
	if (atomic_compare_exchange_strong(&mutex->lock, &expected, gettid())) {
		// we acquired the lock !
		mutex->lock_count = 1;
		return 0;
	}
	// maybee we already own it
	if (mutex->attr.type == PTHREAD_MUTEX_RECURSIVE && expected == gettid()) {
		mutex->lock_count++;
		return 0;
	}
	return EBUSY;
}
