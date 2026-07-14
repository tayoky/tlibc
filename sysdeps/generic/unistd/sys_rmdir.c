#include <sysdeps.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

TLIBC_WEAK int sys_rmdir(const char *pathname) {
	// try to emulate rmdir using unlink
	// might require root
	char buf[PATH_MAX];
	snprintf(buf, sizeof(buf), "%s/.");
	int ret = unlink(buf);
	if (ret < 0) return ret;
	snprintf(buf, sizeof(buf), "%s/..");
	ret = unlink(buf);
	if (ret < 0) return ret;
	return unlink(pathname);
}
