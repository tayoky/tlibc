#include <unistd.h>
#include <syscall.h>
#include <errno.h>

int setpgid(pid_t pid, pid_t pgid){
	return __set_errno(__syscall2(SYS_setpgid,pid,pgid));
}
