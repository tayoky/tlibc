#include <syscall.h>
#include <sysdeps.h>

int sys_tgkill(pid_t pid, pid_t tid, int sig) {
	return __set_errno(__syscall3(SYS_tgkill, pid, tid, sig));
}
