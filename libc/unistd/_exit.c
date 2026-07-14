#include <unistd.h>
#include <sysdeps.h>

TLIBC_NORETURN void _exit(int status) {
	sys_exit(status);
	sys_thread_exit();
	for (;;);
	__builtin_unreachable();
}
