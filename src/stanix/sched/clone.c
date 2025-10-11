#include <sched.h>
#include <syscall.h>
#include <errno.h>

int clone(int (*fn)(void*),void *stack,int flags,void *arg,pid_t *parent_tid,void *tls,pid_t *child_tid){
	(void)parent_tid;
	return __set_errno(__syscall6(SYS_clone,(long)fn,(long)stack,flags,(long)arg,(long)tls,(long)child_tid));
}