#include <sys/mount.h>
#include <sysdeps.h>
#include <errno.h>
#include <syscall.h>

int umount(const char *target) {
	return __set_errno(__syscall1(SYS_umount, (long)target));
}
