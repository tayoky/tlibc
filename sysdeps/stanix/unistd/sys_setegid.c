#include <syscall.h>
#include <sysdeps.h>

int sys_setegid(gid_t gid) {
	return __set_errno(__syscall1(SYS_setegid, gid));
}
