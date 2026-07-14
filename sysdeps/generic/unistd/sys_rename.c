#include <sysdeps.h>

TLIBC_WEAK int sys_rename(const char *oldpath, const char *newpath) {
	int ret = sys_link(oldpath, newpath);
	if (ret < 0) return ret;
	return sys_unlink(oldpath);
}
