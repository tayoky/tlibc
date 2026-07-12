#include <sys/futex.h>
#include <sysdeps.h>

int sys_futex_wait(futex_atomic_t *addr, futex_val_t val) {
	return futex((long*)addr, FUTEX_WAIT, val);
}
