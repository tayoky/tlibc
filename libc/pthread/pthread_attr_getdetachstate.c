#include <pthread.h>
#include <errno.h>

int pthread_attr_getdetachstate(const pthread_attr_t *restrict attr, int *restrict detachstate) {
	if (!attr) return EINVAL;
	*detachstate = attr->detach_state;
	return 0;
}
