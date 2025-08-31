#include <unistd.h>
#include <syscall.h>
#include <errno.h>

int usleep(useconds_t usec){
	return __set_errno(__syscall1(SYS_usleep,usec));
}
