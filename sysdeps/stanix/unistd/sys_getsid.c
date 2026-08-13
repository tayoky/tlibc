#include <syscall.h>
#include <sysdeps.h>

pid_t sys_getsid(void) {
	return __set_errno(__syscall0(SYS_getsid));
}
