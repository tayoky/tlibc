#include <sys/stat.h>
#include <syscall.h>
#include <errno.h>

int fchown(int fd, uid_t owner, gid_t group){
	return __set_errno(__syscall3(SYS_fchown,fd,owner,group));
}
