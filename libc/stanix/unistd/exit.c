#include <stdnoreturn.h>
#include <unistd.h>
#include <syscall.h>

noreturn void _exit(int status){
	__syscall1(SYS_exit,(long)status);
	__builtin_unreachable();
}
