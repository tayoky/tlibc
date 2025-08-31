#include <sys/mount.h>
#include <syscall.h>
#include <errno.h>

int mount(const char *source,const char *target,const char *filesystemtype,unsigned long mountflags,const void *data){
	return __set_errno(__syscall5(SYS_mount,(long)source,(long)target,(long)filesystemtype,(long)mountflags,(long)data));
}
