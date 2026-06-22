#include <pthread.h>
#include <errno.h>

int pthread_barrierattr_init(pthread_barrierattr_t *barrierattr) {
	if (!barrierattr) return EINVAL;
	barrierattr->pshared = PTHREAD_PROCESS_PRIVATE;
	return 0;
}
