#include <sys/syscall.h>
#include <sysdeps.h>
#include <unistd.h>

TLIBC_NORETURN void sys_exit(int status) {
	syscall(SYS_exit_group, status);
	__builtin_unreachable();
}
