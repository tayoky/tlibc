#include <pthread.h>
#include <errno.h>

int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate) {
	if (!attr) return EINVAL;
	if (detachstate > PTHREAD_CREATE_DETACHED) return EINVAL;
	attr->detach_state = detachstate;
	return 0;
}
