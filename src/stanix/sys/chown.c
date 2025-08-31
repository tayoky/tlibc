#include <sys/stat.h>
#include <syscall.h>
#include <errno.h>

int chown(const char *pathname, uid_t owner, gid_t group){
	return __set_errno(__syscall3(SYS_chown,(long)pathname,owner,group));
}
