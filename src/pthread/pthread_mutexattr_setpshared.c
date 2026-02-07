#include <pthread.h>
#include <errno.h>

int pthread_mutexattr_setpshared(pthread_mutexattr_t *mutexattr, int pshared) {
	if (!mutexattr) return __set_errno(-EINVAL);
	mutexattr->pshared = pshared;
	return 0;
}
