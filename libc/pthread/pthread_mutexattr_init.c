#include <pthread.h>
#include <errno.h>

int pthread_mutexattr_init(pthread_mutexattr_t *mutexattr) {
	if (!mutexattr) return __set_errno(-EINVAL);
	mutexattr->protocol = PTHREAD_PRIO_NONE;
	mutexattr->type     = PTHREAD_MUTEX_DEFAULT;
	mutexattr->pshared  = PTHREAD_PROCESS_PRIVATE;
	return 0;
}
