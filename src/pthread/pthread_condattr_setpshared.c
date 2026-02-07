#include <pthread.h>
#include <errno.h>

int pthread_condattr_setpshared(pthread_condattr_t *condattr, int pshared) {
	if (!condattr) return __set_errno(-EINVAL);
	condattr->pshared = pshared;
	return 0;
}
