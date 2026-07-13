#include <errno.h>
#include <syscall.h>
#include <sysdeps.h>

int sys_clock_settime(clockid_t clockid, const struct timespec *tp) {
	return __set_errno(__syscall2(SYS_clock_settime, clockid, (long)tp));
}
