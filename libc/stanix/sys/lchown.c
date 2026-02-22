#include <sys/stat.h>
#include <syscall.h>
#include <errno.h>

int lchown(const char *pathname, uid_t owner, gid_t group){
	return __set_errno(__syscall3(SYS_lchown,(long)pathname,owner,group));
}
