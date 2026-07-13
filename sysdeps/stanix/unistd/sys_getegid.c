#include <syscall.h>
#include <sysdeps.h>

gid_t sys_getegid(void) {
	return __set_errno(__syscall0(SYS_getegid));
}
