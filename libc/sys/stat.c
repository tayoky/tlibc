#include <sys/stat.h>
#include <sysdeps.h>

int stat(const char *pathname, struct stat *buf) {
	return sys_stat(pathname, buf);
}
