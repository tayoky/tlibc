#include <sysdeps.h>

TLIBC_WEAK int sys_nanosleep(const struct timespec *duration, struct timespec *rem) {
	return __set_errno(-ENOSYS);
}
