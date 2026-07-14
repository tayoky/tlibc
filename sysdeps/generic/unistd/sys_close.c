#include <sysdeps.h>

TLIBC_WEAK int sys_close(int fd) {
	return SYSDEP_STUB;
}
