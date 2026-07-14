#include <sysdeps.h>

TLIBC_WEAK TLIBC_NORETURN void sys_exit(int status) {
	(void)status;
	for (;;);
	__builtin_unreachable();
}
