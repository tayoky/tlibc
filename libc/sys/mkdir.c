#include <sys/stat.h>
#include <sysdeps.h>

int mkdir(const char *pathname, mode_t mode) {
	return sys_mkdir(pathname, mode);
}
