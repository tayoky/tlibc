#include <syscall.h>
#include <sysdeps.h>
#include <tlibcnoreturn.h>
#include <unistd.h>

int sys_exit(int status) {
	return __set_errno(__syscall1(SYS_exit, (long)status));
}
