#include <sysdeps.h>

TLIBC_WEAK int sys_close(int fd) {
	return __set_errno(-ENOSYS);
}
