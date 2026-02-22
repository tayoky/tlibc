#include <unistd.h>
#include <syscall.h>
#include <errno.h>

int setgid(gid_t gid){
	return __set_errno(__syscall1(SYS_setgid,gid));
}
