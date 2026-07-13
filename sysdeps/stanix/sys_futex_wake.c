#include <sys/futex.h>
#include <limits.h>
#include <sysdeps.h>

int sys_futex_wake(futex_atomic_t *addr, int count) {
	return futex((long*)addr, FUTEX_WAKE, count == INT_MAX ? LONG_MAX : count);
}
