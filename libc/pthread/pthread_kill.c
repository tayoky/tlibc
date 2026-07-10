#include <pthread.h>
#include <signal.h>
#include <tlibc.h>
#include <errno.h>

int pthread_kill(pthread_t thread, int sig) {
	int ret = kill(thread->tid, sig);
	if (ret < 0) return errno;
	return 0;
}
