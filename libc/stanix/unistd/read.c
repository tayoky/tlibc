#include <unistd.h>
#include <syscall.h>
#include <errno.h>

ssize_t read(int fd, const void *buffer, size_t count){
	return __set_errno(__syscall3(SYS_read,fd,(long)buffer,count));
}
