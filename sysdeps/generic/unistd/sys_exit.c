#include <sysdeps.h>

TLIBC_WEAK int sys_exit(int status) {
	return __set_errno(-ENOSYS);
}
