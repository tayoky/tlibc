#include <pthread.h>
#include <errno.h>

int pthread_barrierattr_getpshared(const pthread_barrierattr_t *restrict barrierattr, int *restrict pshared) {
	if (!barrierattr) return EINVAL;
	*pshared = barrierattr->pshared;
	return 0;
}
