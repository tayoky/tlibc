#include <errno.h>
#include <pthread.h>

int pthread_mutexattr_setprotocol(pthread_mutexattr_t *mutexattr, int protocol) {
	if (!mutexattr) return EINVAL;
	mutexattr->protocol = protocol;
	return 0;
}
