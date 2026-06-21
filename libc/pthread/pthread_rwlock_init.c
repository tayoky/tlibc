#include <pthread.h>
#include <errno.h>

int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr) {
	if (!rwlock) return EINVAL;
	if (rwlock->initalized) return EBUSY;
	rwlock->initalized = 1;
	if (attr) {
		rwlock->attr = *attr;
	} else {
		pthread_rwlockattr_init(&rwlock->attr);
	}
	rwlock->lock = 0;
	return 0;
}
