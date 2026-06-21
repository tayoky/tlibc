#include <pthread.h>
#include <errno.h>

int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *restrict attr, int *restrict pshared) {
	if (!attr) return EINVAL;
	*pshared = attr->pshared;
	return 0;
}
