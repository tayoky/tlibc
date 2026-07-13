#include <syscall.h>
#include <sysdeps.h>

int sys_setuid(uid_t uid) {
	return __set_errno(__syscall1(SYS_setuid, uid));
}
