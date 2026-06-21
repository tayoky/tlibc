#include <errno.h>
#include <pthread.h>

int pthread_mutexattr_setpshared(pthread_mutexattr_t *mutexattr, int pshared) {
	if (!mutexattr) return EINVAL;
	mutexattr->pshared = pshared;
	return 0;
}
