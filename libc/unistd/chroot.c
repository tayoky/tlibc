#include <sysdeps.h>
#include <syscall.h>

int chroot(const char *pathname) {
	return sys_chroot(pathname);
}
