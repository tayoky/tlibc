#include <sysdeps.h>

TLIBC_WEAK int sys_fcntl(int fd, int op, va_list args) {
	return SYSDEP_STUB;
}
