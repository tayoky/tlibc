#include <pthread.h>
#include <errno.h>

int pthread_mutexattr_settype(pthread_mutexattr_t *mutexattr, int type) {
	if (!mutexattr) return __set_errno(-EINVAL);
	mutexattr->type = type;
	return 0;
}
