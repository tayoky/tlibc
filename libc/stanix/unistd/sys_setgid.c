#include <syscall.h>
#include <sysdeps.h>

int sys_setgid(gid_t gid) {
	return __set_errno(__syscall1(SYS_setgid, gid));
}
