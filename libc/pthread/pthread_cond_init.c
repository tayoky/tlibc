#include <pthread.h>
#include <errno.h>

int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr) {
	if (!cond) return EINVAL;
	if (cond->initalized) return EBUSY;
	cond->initalized = 1;
	if (attr) {
		cond->attr = *attr;
	} else {
		pthread_condattr_init(&cond->attr);
	}
	cond->seq = 0;
	return 0;
}
