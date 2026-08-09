#include <pthread.h>
#include <tlibc.h>

int pthread_detach(pthread_t thread) {
	if (!thread) {
		return ESRCH;
	}
	if (atomic_exchange(&thread->detach_state, PTHREAD_CREATE_DETACHED) != PTHREAD_CREATE_JOINABLE) {
		return EINVAL;
	}
	atomic_store(&thread->futex, 1);
	sys_futex_wake(&thread->futex, INT_MAX);
	thread->detach_state = PTHREAD_CREATE_DETACHED;
	return 0;
}
