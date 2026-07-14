#include <unistd.h>
#include <sysdeps.h>

int link(const char *oldpath, const char *newpath) {
	return sys_link(oldpath, newpath);
}
