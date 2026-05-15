#include <errno.h>
#include <pthread.h>

int pthread_mutexattr_getpshared(const pthread_mutexattr_t *restrict mutexattr, int *restrict pshared) {
	if (!mutexattr) return __set_errno(-EINVAL);
	*pshared = mutexattr->pshared;
	return 0;
}
