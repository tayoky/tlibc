#include <pthread.h>
#include <errno.h>

int pthread_condattr_getpshared(const pthread_condattr_t *restrict condattr, int *restrict pshared) {
	if (!condattr) return __set_errno(-EINVAL);
	*pshared = condattr->pshared;
	return 0;
}
