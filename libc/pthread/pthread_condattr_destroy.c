#include <errno.h>
#include <pthread.h>

int pthread_condattr_destroy(pthread_condattr_t *condattr) {
	if (!condattr) return EINVAL;
	return 0;
}
