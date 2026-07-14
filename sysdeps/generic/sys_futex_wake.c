#include <sysdeps.h>

TLIBC_WEAK int sys_futex_wake(futex_atomic_t *addr, int count) {
	return __set_errno(-ENOSYS);
}
