#include <errno.h>
#include <pthread.h>

int pthread_mutexattr_settype(pthread_mutexattr_t *mutexattr, int type) {
	if (!mutexattr) return EINVAL;
	mutexattr->type = type;
	return 0;
}
