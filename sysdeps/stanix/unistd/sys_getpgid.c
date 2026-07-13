#include <errno.h>
#include <syscall.h>
#include <unistd.h>

pid_t getpgid(pid_t pid) {
	return __set_errno(__syscall1(SYS_getpgid, pid));
}
