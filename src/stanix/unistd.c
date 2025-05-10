#include <unistd.h>
#include <syscall.h>
#include <stdint.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/type.h>
#include <sys/types.h>
#include <stdio.h>
#include <poll.h>

ssize_t read(int fd, const void *buffer, size_t count){
	return __set_errno(__syscall3(SYS_read,fd,(long)buffer,count));
}

ssize_t write(int fd, const void *buffer, size_t count){
	return __set_errno(__syscall3(SYS_write,fd,(long)buffer,count));
}

int dup(int oldfd){
	return __set_errno(__syscall1(SYS_dup,(long)oldfd));
}
int dup2(int oldfd, int newfd){
	return __set_errno(__syscall2(SYS_dup2,(long)oldfd,(long)newfd));
}

off_t lseek(int fd, off_t offset, int whence){
	return __set_errno(__syscall3(SYS_seek,fd,(long)offset,whence));
}

int unlink(const char *pathname){
	return __set_errno(__syscall1(SYS_unlink,(long)pathname));
}
int rmdir(const char *pathname){
	return __set_errno(__syscall1(SYS_rmdir,(long)pathname));
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
	__syscall1(SYS_exit,(long)status);
}

unsigned int sleep(unsigned int seconds){
	return usleep(seconds * 1000000);
}
int usleep(useconds_t usec){
	return __syscall1(SYS_usleep,usec);
}

int gettimeofday(struct timeval *tv,struct timezone *tz){
	return __set_errno(__syscall2(SYS_gettimeofday,(long)tv,(long)tz));
}

int pipe(int pipefd[2]){
	return __set_errno(__syscall1(SYS_pipe,(long)pipefd));
}

int execve(const char *pathname,const char * const *argv,const char * const *envp){
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

int chdir(const char *path){
	return __set_errno(__syscall1(SYS_chdir,(long)path));
}

int isatty(int fd){
	int ret = __syscall1(SYS_isatty,(long)fd);
	//isatty is a bit diferent at it should return 0 and not -1;
	if(ret < 0){
		errno = -ret;
		return 0;
	}

	return ret;
}

//technicly not part of unistd.h but anyway
int poll(struct pollfd *fds, nfds_t nfds, int timeout){
	return __set_errno(__syscall3(SYS_poll,(long)fds,(long)nfds,(long)timeout));
}