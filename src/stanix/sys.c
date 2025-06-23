#include <syscall.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/module.h>
#include <sys/mount.h>
#include <sys/mman.h>

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

int mount(const char *source,const char *target,const char *filesystemtype,unsigned long mountflags,const void *data){
	return __set_errno(__syscall5(SYS_mount,(long)source,(long)target,(long)filesystemtype,(long)mountflags,(long)data));
}

int umount(const char *target){
	return __set_errno(__syscall1(SYS_umount,(long)target));
}

void *mmap(void *addr,size_t length,int prot,int flags,int fd,off_t offset){
	void *ret = (void *)__syscall6(SYS_mmap,(long)addr,length,prot,flags,fd,offset);
	if(ret >  (void *)0xFFFFF00000000000){
		errno = -(long)ret;
		return map_failed;
	}

	return ret;
}

int munmap(void *addr,size_t length){
	return __set_errno(__syscall2(SYS_munmap,(long)addr,length));
}
int mprotect(void *addr,size_t size,int prot){
	return __set_errno(__syscall3(SYS_mprotect,(long)addr,size,prot));
}