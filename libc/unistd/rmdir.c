#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <sysdeps.h>

int rmdir(const char *pathname) {
	if (sys_rmdir) {
		return sys_rmdir(pathname);
	} else if (sys_unlink) {
		char buf[PATH_MAX];
		snprintf(buf, sizeof(buf), "%s/.");
		int ret = sys_unlink(buf);
		if (ret < 0) return ret;
		snprintf(buf, sizeof(buf), "%s/..");
		ret = sys_unlink(buf);
		if (ret < 0) return ret;
		return sys_unlink(pathname);
	} else {
		return __set_errno(-ENOSYS);
	}
}
