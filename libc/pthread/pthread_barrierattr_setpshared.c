#include <pthread.h>
#include <errno.h>

int pthread_barrierattr_setpshared(pthread_barrierattr_t *barrierattr, int pshared) {
	if (!barrierattr) return EINVAL;
	if (pshared > PTHREAD_PROCESS_SHARED) return EINVAL;
	barrierattr->pshared = pshared;
	return 0;
}
