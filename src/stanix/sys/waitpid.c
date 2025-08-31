#include <sys/wait.h>
#include <syscall.h>
#include <errno.h>

pid_t waitpid(pid_t pid, int *status, int options){
	return __set_errno(__syscall3(SYS_waitpid,(long)pid,(long)status,(long)options));
}
