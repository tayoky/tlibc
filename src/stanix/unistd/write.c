#include <unistd.h>
#include <syscall.h>
#include <errno.h>

ssize_t write(int fd, const void *buffer, size_t count){
	return __set_errno(__syscall3(SYS_write,fd,(long)buffer,count));
}
