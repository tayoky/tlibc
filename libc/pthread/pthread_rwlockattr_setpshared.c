#include <pthread.h>
#include <errno.h>

int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *attr, int pshared) {
	if (!attr) return EINVAL;
	if (pshared > PTHREAD_PROCESS_SHARED) return EINVAL;
	attr->pshared = pshared;
	return 0;
}
