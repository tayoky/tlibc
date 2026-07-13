#include <sysdeps.h>
#include <sys/syscall.h>
#include <unistd.h>

#ifdef SYS_open
int sys_open(const char *pathname, int flags, mode_t mode) {
	return syscall(SYS_open, pathname, flags, mode);
}
#endif
