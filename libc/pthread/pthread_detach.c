#include <pthread.h>
#include <tlibc.h>

int pthread_detach(pthread_t thread) {
	if (!thread) {
		return ESRCH;
	}
	if (thread->detach_state != PTHREAD_CREATE_JOINABLE) {
		return EINVAL;
	}
	// FIXME : we have a race here
	// if others threads also try to wait/detach
	// or if the thread is already dead
	thread->detach_state = PTHREAD_CREATE_DETACHED;
	return 0;
}
