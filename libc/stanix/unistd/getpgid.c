#include <unistd.h>
#include <syscall.h>
#include <errno.h>

pid_t getpgid(pid_t pid){
	return __set_errno(__syscall1(SYS_getpgid,pid));
}
