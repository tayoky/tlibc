#include <pthread.h>
#include <errno.h>

int pthread_barrierattr_destroy(pthread_barrierattr_t *barrierattr) {
	if (!barrierattr) return EINVAL;
	return 0;
}
