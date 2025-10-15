#include <sched.h>
#include <syscall.h>
#include <errno.h>

int stanix_new_thread(void (*fn)(void*),void *stack,int flags,void *arg,void *tls,pid_t *child_tid){
	return __set_errno(__syscall6(SYS_new_thread,(long)fn,(long)stack,flags,(long)arg,(long)tls,(long)child_tid));
}