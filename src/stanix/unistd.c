#include <unistd.h>
#include <syscall.h>
#include <stdint.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/type.h>

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

unsigned int sleep(unsigned int seconds){
	return (int)usleep(seconds * 1000000) / 1000000;
}
int usleep(useconds_t usec){
	return __syscall1(SYS_usleep,usec);
}

int gettimeofday(struct timeval *tv,struct timezone *tz){
	return __set_errno(__syscall2(SYS_gettimeoftheday,(long)tv,(long)tz));
}

int ioctl(int fd, unsigned long op, ...){
	//TODO : support for arg
	return __set_errno(__syscall3(SYS_ioctl,fd,op,NULL));
}

int pipe(int pipefd[2]){
	return __set_errno(__syscall1(SYS_pipe,(long)pipefd));
}