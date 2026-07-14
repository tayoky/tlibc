#include <sysdeps.h>

TLIBC_WEAK TLIBC_NORETURN void sys_thread_exit(void) {
	for (;;);
	__builtin_unreachable();
}
