#include <pthread.h>
#include <errno.h>

int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *restrict mutexattr, int *restrict protocol) {
	if (!mutexattr) return __set_errno(-EINVAL);
	*protocol = mutexattr->protocol;
	return 0;
}
