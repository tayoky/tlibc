#include <sys/stat.h>
#include <sysdeps.h>
#include <errno.h>
#include <syscall.h>

int sys_fchown(int fd, uid_t owner, gid_t group) {
	return __set_errno(__syscall3(SYS_fchown, fd, owner, group));
}
