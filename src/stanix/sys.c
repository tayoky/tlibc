#include <syscall.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/module.h>
#include <sys/mount.h>

int ioctl(int fd,unsigned long op,void *arg){
	return __set_errno(__syscall3(SYS_ioctl,fd,op,(long)arg));
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

//TODO : make this when the kernel will get support for it
pid_t wait(int *status);

pid_t waitpid(pid_t pid, int *status, int options){
	return __set_errno(__syscall3(SYS_waitpid,(long)pid,(long)status,(long)options));
}

int insmod(const char *pathname,const char **argv){
	return __set_errno(__syscall2(SYS_insmod,(long)pathname,(long)argv));
}

int rmmod(const char *name){
	return __set_errno(__syscall1(SYS_rmmod,(long)name));
}

int umount(const char *target){
	return __set_errno(__syscall1(SYS_umount,(long)target));
}