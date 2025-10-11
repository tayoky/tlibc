#include <pthread.h>
#include <syscall.h>

void pthread_exit(void *retval){
	__syscall1(SYS_thread_exit,(long)retval);
}