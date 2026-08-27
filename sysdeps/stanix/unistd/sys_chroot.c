#include <sysdeps.h>
#include <syscall.h>

int sys_chroot(const char *path) {
	return __set_errno(__syscall1(SYS_chroot, (long)path));
}
