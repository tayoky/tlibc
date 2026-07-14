#include <sysdeps.h>

TLIBC_WEAK int sys_thread_exit(void) {
	return __set_errno(-ENOSYS);
}
