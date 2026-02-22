#include <pthread.h>
#include <errno.h>

int pthread_mutexattr_gettype(const pthread_mutexattr_t *restrict mutexattr, int *restrict type) {
	if (!mutexattr) return __set_errno(-EINVAL);
	*type = mutexattr->type;
	return 0;
}
