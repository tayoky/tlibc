#include <sysdeps.h>

TLIBC_WEAK int sys_futex_wait(futex_atomic_t *addr, futex_val_t val) {
	return __set_errno(-ENOSYS);
}
