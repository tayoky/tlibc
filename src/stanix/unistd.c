#include <unistd.h>
#include <syscall.h>
#include <stdint.h>

ssize_t read(int fd, const void *buffer, size_t count){
	return __syscall3(SYS_read,fd,(long)buffer,count);
}

ssize_t write(int fd, const void *buffer, size_t count){
	return __syscall3(SYS_write,fd,(long)buffer,count);
}

off_t lseek(int fd, off_t offset, int whence){
	return (off_t)__syscall3(SYS_seek,fd,(long)offset,whence);
}

void *sbrk(intptr_t increment){
	//save the current sbrk beauce stanix's sbrk return the new heao end
	//not the previous like linux
	uint64_t prev_brk = __syscall1(SYS_sbrk,0);

	__syscall1(SYS_sbrk,increment);

	return (void*)prev_brk;
}