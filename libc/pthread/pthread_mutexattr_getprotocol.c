#include <errno.h>
#include <pthread.h>

int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *restrict mutexattr, int *restrict protocol) {
	if (!mutexattr) return EINVAL;
	*protocol = mutexattr->protocol;
	return 0;
}
