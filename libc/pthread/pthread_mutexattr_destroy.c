#include <errno.h>
#include <pthread.h>

int pthread_mutexattr_destroy(pthread_mutexattr_t *mutexattr) {
	if (!mutexattr) return EINVAL;
	// invalidate the type to trigger errors
	mutexattr->type = 42;
	return 0;
}
