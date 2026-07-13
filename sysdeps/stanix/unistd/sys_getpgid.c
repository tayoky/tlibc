#include <errno.h>
#include <syscall.h>
#include <sysdeps.h>

pid_t sys_getpgid(pid_t pid) {
	return __set_errno(__syscall1(SYS_getpgid, pid));
}
