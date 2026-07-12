#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <sysdeps.h>

int sys_mkdir(const char *pathname, mode_t mode) {
	if (sys_mkdir) {
		return sys_mkdir(pathname, mode);
	} else if (sys_mknod) {
		// please update your unix :(
		int ret = sys_mknod(pathname, mode, S_IFDIR);
		if (ret < 0) return ret;
		char buf[PATH_MAX];
		snprintf(buf, sizeof(buf), "%s/.", pathname);
		return link(pathname, buf);
	} else {
		return __set_errno(-ENOSYS);
	}
}
