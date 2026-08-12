#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <tlibc.h>
#include <errno.h>

int pthread_sigqueue(pthread_t thread, int sig, const union sigval value) {
	int ret = tgsigqueue(getpid(), thread->tid, sig, value);
	if (ret < 0) return errno;
	return 0;
}
