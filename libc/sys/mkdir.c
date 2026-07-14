#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <sysdeps.h>

int mkdir(const char *pathname, mode_t mode) {
	int ret = sys_mkdir(pathname, mode);
	if (ret < 0 && errno == ENOSYS) {
		// please update your unix :(
		ret = sys_mknod(pathname, mode, S_IFDIR);
		if (ret < 0) return ret;
		char buf[PATH_MAX];
		snprintf(buf, sizeof(buf), "%s/.", pathname);
		ret = link(pathname, buf);
	}
	return ret;
}
