#include <sysdeps.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

int pthread_mutex_unlock(pthread_mutex_t *mutex) {
	if (!mutex) return EINVAL;

	if (atomic_load(&mutex->lock) != (futex_val_t)gettid()) {
		return EPERM;
	}

	if (mutex->attr.type == PTHREAD_MUTEX_RECURSIVE) {
		mutex->lock_count--;
		if (mutex->lock_count != 0) return 0;
	}
	atomic_store(&mutex->lock, 0);
	sys_futex_wake(&mutex->lock, 1);

	return 0;
}
