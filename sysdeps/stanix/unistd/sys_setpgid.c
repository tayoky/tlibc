#include <errno.h>
#include <syscall.h>
#include <sysdeps.h>

int sys_setpgid(pid_t pid, pid_t pgid) {
	return __set_errno(__syscall2(SYS_setpgid, pid, pgid));
}
