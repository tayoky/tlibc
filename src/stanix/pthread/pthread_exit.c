#include <pthread.h>
#include <syscall.h>
#include <stdnoreturn.h>

noreturn void pthread_exit(void *retval){
	__syscall1(SYS_thread_exit,(long)retval);
	__builtin_unreachable();
}