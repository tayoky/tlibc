#include <sysdeps.h>
#include <pthread.h>
#include <limits.h>
#include <errno.h>

int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock) {
	if (!rwlock) return EINVAL;

	futex_val_t expected = 0;
	while (expected != TLIBC_FUTEX_MAX) {
		if (atomic_compare_exchange_strong(&rwlock->lock, &expected, expected + 1)) {
			// we acquired the lock
			return 0;
		}
	}

	// lock already held for write
	return EBUSY;
}
