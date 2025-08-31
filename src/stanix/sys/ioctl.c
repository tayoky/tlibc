#include <sys/ioctl.h>
#include <syscall.h>
#include <errno.h>

int ioctl(int fd,unsigned long op,void *arg){
	return __set_errno(__syscall3(SYS_ioctl,fd,op,(long)arg));
}
