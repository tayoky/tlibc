#include <sysdeps.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>

#ifdef SYS_open
int sys_open(const char *pathname, int flags, mode_t mode) {
	return syscall(SYS_open, pathname, flags, mode);
}
#else
int sys_open(const char *pathname, int flags, mode_t mode) {
	return sys_openat(AT_FDCWD, pathname, flags, mode);
}
#endif
