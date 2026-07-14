#include <syscall.h>
#include <sysdeps.h>
#include <tlibcnoreturn.h>
#include <unistd.h>

TLIBC_NORETURN void sys_exit(int status) {
	__set_errno(__syscall1(SYS_exit, (long)status));
	__builtin_unreachable();
}
