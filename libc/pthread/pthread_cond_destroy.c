#include <pthread.h>
#include <errno.h>

int pthread_cond_destroy(pthread_cond_t *cond) {
	if (!cond || !cond->initalized) return EINVAL;
	cond->initalized = 0;
	return 0;
}
