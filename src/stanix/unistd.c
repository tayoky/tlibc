#include <unistd.h>
#include <syscall.h>
#include <stdint.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/type.h>
#include <sys/types.h>
#include <stdio.h>

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

int pipe(int pipefd[2]){
	return __set_errno(__syscall1(SYS_pipe,(long)pipefd));
}

int execve(const char *pathname,const char **argv,const char **envp){
	return __set_errno(__syscall3(SYS_execve,(long)pathname,(long)argv,(long)envp));
}

int mkdir(const char *pathname,mode_t mode){
	return __set_errno(__syscall2(SYS_mkdir,(long)pathname,(long)mode));
}

pid_t fork(void){
	return __set_errno(__syscall0(SYS_fork));
}

char *getcwd(char *buf, size_t size){
	if(__set_errno(__syscall2(SYS_getcwd,(long)buf,(long)size))){
		return NULL;
	} else{
		return buf;
	}
}