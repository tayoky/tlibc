#include <syscall.h>
#include <sysdeps.h>

int sys_kill(pid_t pid, int sig) {
	return __set_errno(__syscall2(SYS_kill, pid, sig));
}
