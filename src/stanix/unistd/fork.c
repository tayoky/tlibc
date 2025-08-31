#include <unistd.h>
#include <syscall.h>
#include <errno.h>

pid_t fork(void){
	return __set_errno(__syscall0(SYS_fork));
}
