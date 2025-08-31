#include <unistd.h>
#include <syscall.h>
#include <errno.h>

pid_t getpid(){
	return __set_errno(__syscall0(SYS_getpid));
}
