#include <sysdeps.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>

TLIBC_WEAK int sys_mkdir(const char *pathname, mode_t mode) {
	// won't work on most OSes but we can try
	int ret = sys_mknod(pathname, mode, S_IFDIR);
	if (ret < 0) return ret;
	char buf[PATH_MAX];
	snprintf(buf, sizeof(buf), "%s/.", pathname);
	return sys_link(pathname, buf);
}
