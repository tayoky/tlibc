#include <unistd.h>
#include <syscall.h>
#include <errno.h>

int ftruncate(int fd, off_t length){
	return __set_errno(__syscall2(SYS_ftruncate,fd,(long)length));
}
