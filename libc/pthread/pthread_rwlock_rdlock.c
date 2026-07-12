#include <sysdeps.h>
#include <pthread.h>
#include <limits.h>
#include <errno.h>

int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock) {
	if (!rwlock) return EINVAL;

	for (;;) {
		futex_val_t expected = 0;
		while (expected != TLIBC_FUTEX_MAX) {
			if (atomic_compare_exchange_strong(&rwlock->lock, &expected, expected + 1)) {
				// we acquired the lock
				return 0;
			}
		}
		sys_futex_wait(&rwlock->lock, expected);
	}
	return 0;
}
