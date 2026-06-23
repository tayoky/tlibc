#include <errno.h>
#include <pthread.h>

int pthread_condattr_getpshared(const pthread_condattr_t *restrict condattr, int *restrict pshared) {
	if (!condattr) return EINVAL;
	*pshared = condattr->pshared;
	return 0;
}
