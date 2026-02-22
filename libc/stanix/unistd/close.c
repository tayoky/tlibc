#include <unistd.h>
#include <syscall.h>
#include <errno.h>

int close(int fd){
	return __set_errno(__syscall1(SYS_close,(long)fd));
}
