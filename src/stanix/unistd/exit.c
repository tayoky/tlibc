#include <unistd.h>
#include <syscall.h>

void _exit(int status){
	__syscall1(SYS_exit,(long)status);
}
