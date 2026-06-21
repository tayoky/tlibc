#include <sys/futex.h>
#include <pthread.h>
#include <limits.h>
#include <errno.h>

int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock) {
	if (!rwlock) return EINVAL;
	
	for (;;) {
		long expected = 0;
		if (atomic_compare_exchange_strong(&rwlock->lock, &expected, LONG_MAX)) {
			// we acquired
			break;
		}
		futex((long*)&rwlock->lock, FUTEX_WAIT, expected);
	}
	return 0;
}
