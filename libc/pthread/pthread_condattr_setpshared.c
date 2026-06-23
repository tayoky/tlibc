#include <errno.h>
#include <pthread.h>

int pthread_condattr_setpshared(pthread_condattr_t *condattr, int pshared) {
	if (!condattr) return EINVAL;
	if (pshared > PTHREAD_PROCESS_SHARED) return EINVAL;
	condattr->pshared = pshared;
	return 0;
}
