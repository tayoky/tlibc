#include <sys/stat.h>
#include <sysdeps.h>

int lstat(const char *pathname, struct stat *buf) {
	return sys_lstat(pathname, buf);
}
