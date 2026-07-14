#include <sysdeps.h>

TLIBC_WEAK int sys_new_thread(void (*fn)(void*), void *stack, int flags, void *arg, pid_t *child_tid) {
	return __set_errno(-ENOSYS);
}
