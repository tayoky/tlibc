#include <pthread.h>
#include <syscall.h>
#include <stdnoreturn.h>

void noreturn pthread_exit(void *retval){
	__syscall1(SYS_thread_exit,(long)retval);
}