#include <errno.h>
#include <syscall.h>
#include <unistd.h>

int setegid(gid_t gid) {
	return __set_errno(__syscall1(SYS_setegid, gid));
}
