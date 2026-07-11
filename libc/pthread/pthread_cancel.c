#include <pthread.h>
#include <tlibc.h>

int pthread_cancel(pthread_t thread) {
	// TODO : async mode
	thread->cancel = 1;
	return 0;
}
