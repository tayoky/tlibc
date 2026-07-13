#include <sysdeps.h>
#include <sys/syscall.h>
#include <unistd.h>

#ifdef SYS_openat
int sys_openat(int dirfd, const char *pathname, int flags, mode_t mode) {
	return syscall(SYS_openat, dirfd, pathname, flags, mode);
}
#endif
