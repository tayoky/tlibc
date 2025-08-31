#include <sys/mount.h>
#include <syscall.h>
#include <errno.h>

int umount(const char *target){
	return __set_errno(__syscall1(SYS_umount,(long)target));
}
