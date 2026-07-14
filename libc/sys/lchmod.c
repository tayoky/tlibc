#include <sys/stat.h>
#include <sysdeps.h>

int lchmod(const char *pathname, mode_t mode) {
	return sys_lchmod(pathname, mode);
}
