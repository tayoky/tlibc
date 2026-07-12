#include <sysdeps.h>
#include <pthread.h>
#include <limits.h>
#include <errno.h>

int pthread_rwlock_unlock(pthread_rwlock_t *rwlock) {
	if (!rwlock) return EINVAL;
	
	futex_val_t val = atomic_load(&rwlock->lock);
	if (val == TLIBC_FUTEX_MAX) {
		// we had the write lock
		atomic_store(&rwlock->lock, 0);
		sys_futex_wake(&rwlock->lock, INT_MAX);
	} else {
		// we had the read lock
		if (atomic_fetch_sub(&rwlock->lock, 1) == 1) {
			// we held the last read lock
			sys_futex_wake(&rwlock->lock, 1);
		}
	}
	return 0;
}
