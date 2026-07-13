#include <syscall.h>
#include <sysdeps.h>

pid_t sys_gettid(void) {
	return __set_errno(__syscall0(SYS_gettid));
}
