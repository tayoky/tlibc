#include <pthread.h>
#include <errno.h>

int pthread_mutexattr_setprotocol(pthread_mutexattr_t *mutexattr, int protocol) {
	if (!mutexattr) return __set_errno(-EINVAL);
	mutexattr->protocol = protocol;
	return 0;
}
