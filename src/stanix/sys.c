#include <syscall.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

int ioctl(int fd,unsigned long op,void *arg){
	return __set_errno(__syscall3(SYS_ioctl,fd,op,arg));
}

int fstat(int fd,struct stat *st){
	return __set_errno(__syscall2(SYS_stat,(long)fd,(long)st));
}

int stat(const char *pathname,struct stat *st){
	return __set_errno(__syscall2(SYS_stat,(long)pathname,(long)st));
}

//when writing this link don't exist in stanix
//so lstat in not implemented
int lstat(const char *pathname,struct stat *st){
	return stat(pathname,st);
}