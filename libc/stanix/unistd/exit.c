#include <tlibcnoreturn.h>
#include <unistd.h>
#include <syscall.h>

TLIBC_NORETURN void _exit(int status){
	__syscall1(SYS_exit,(long)status);
	__builtin_unreachable();
}
