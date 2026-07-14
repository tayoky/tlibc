#include <sysdeps.h>

TLIBC_WEAK int sys_join_thread(pid_t tid, void **arg) {
	return __set_errno(-ENOSYS);
}
