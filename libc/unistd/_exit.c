#include <unistd.h>
#include <sysdeps.h>

TLIBC_NORETURN void _exit(int status) {
	if (sys_exit) {
		sys_exit(status);
	}
	if (sys_thread_exit) {
		sys_thread_exit();
	}
	for (;;);
	__builtin_unreachable();
}
