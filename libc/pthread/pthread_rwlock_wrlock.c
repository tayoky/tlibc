#include <sysdeps.h>
#include <pthread.h>
#include <limits.h>
#include <errno.h>

int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock) {
	if (!rwlock) return EINVAL;
	
	for (;;) {
		futex_val_t expected = 0;
		if (atomic_compare_exchange_strong(&rwlock->lock, &expected, TLIBC_FUTEX_MAX)) {
			// we acquired
			break;
		}
		sys_futex_wait(&rwlock->lock, expected);
	}
	return 0;
}
