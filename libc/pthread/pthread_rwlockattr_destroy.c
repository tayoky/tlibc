#include <pthread.h>
#include <errno.h>

int pthread_rwlockattr_destroy(pthread_rwlockattr_t *attr) {
	if (!attr) return EINVAL;
	return 0;
}
