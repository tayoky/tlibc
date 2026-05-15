#include <errno.h>
#include <pthread.h>

int pthread_condattr_destroy(pthread_condattr_t *condattr) {
	if (!condattr) return __set_errno(-EINVAL);
	(void)condattr;
	return 0;
}
