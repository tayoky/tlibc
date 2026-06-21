#include <pthread.h>
#include <errno.h>

int pthread_rwlockattr_init(pthread_rwlockattr_t *attr) {
	if (!attr) return EINVAL;
	attr->pshared = PTHREAD_PROCESS_PRIVATE;
	return 0;
}
