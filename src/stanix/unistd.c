#include <unistd.h>
#include <syscall.h>
#include <stdint.h>
#include <errno.h>

ssize_t read(int fd, const void *buffer, size_t count){
	return __set_errno(__syscall3(SYS_read,fd,(long)buffer,count));
}

ssize_t write(int fd, const void *buffer, size_t count){
	return __set_errno(__syscall3(SYS_write,fd,(long)buffer,count));
}

off_t lseek(int fd, off_t offset, int whence){
	return __set_errno(__syscall3(SYS_seek,fd,(long)offset,whence));
}

int close(int fd){
	return __set_errno(__syscall1(SYS_close,(long)fd));
}

void *sbrk(intptr_t increment){
	//save the current sbrk beauce stanix's sbrk return the new heao end
	//not the previous like linux
	uint64_t prev_brk = __syscall1(SYS_sbrk,0);

	__syscall1(SYS_sbrk,increment);

	return (void*)prev_brk;
}

void _exit(int status){
	__syscall1(SYS_exit,status);
}