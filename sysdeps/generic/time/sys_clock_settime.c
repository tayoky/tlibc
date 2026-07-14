#include <sysdeps.h>

TLIBC_WEAK int sys_clock_settime(clockid_t clockid, const struct timespec *tp) {
	return __set_errno(-ENOSYS);
}
