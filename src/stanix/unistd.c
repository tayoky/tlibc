#include <unistd.h>
#include <syscall.h>

ssize_t read(int fd, const void *buffer, size_t count){
	return __syscall3(SYS_READ,fd,(long)buffer,count);
}

ssize_t write(int fd, const void *buffer, size_t count){
	return __syscall3(SYS_WRITE,fd,(long)buffer,count);
}

off_t lseek(int fd, off_t offset, int whence){
	return (off_t)__syscall3(SYS_SEEK,fd,(long)offset,whence);
}