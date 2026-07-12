#include <stdio.h>
#include <sysdeps.h>

int rename(const char *oldpath, const char *newpath) {
	if (sys_rename) {
		return sys_rename(oldpath, newpath);
	} else if (sys_link && sys_unlink) {
		int ret = sys_link(oldpath, newpath);
		if (ret < 0) return ret;
		return sys_unlink(oldpath);
	} else {
		return __set_errno(-ENOSYS);
	}
}
