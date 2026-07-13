#include <syscall.h>
#include <sysdeps.h>

uid_t sys_geteuid(void) {
	return __set_errno(__syscall0(SYS_geteuid));
}
