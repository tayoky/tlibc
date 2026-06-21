#include <errno.h>
#include <pthread.h>

int pthread_mutexattr_gettype(const pthread_mutexattr_t *restrict mutexattr, int *restrict type) {
	if (!mutexattr) return EINVAL;
	*type = mutexattr->type;
	return 0;
}
