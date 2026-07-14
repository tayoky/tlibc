#include <sysdeps.h>

TLIBC_WEAK int sys_clock_gettime(clockid_t clockid, struct timespec *tp) {
	return __set_errno(-ENOSYS);
}
