#include <sys/stat.h>
#include <sysdeps.h>

int mknod(const char *pathname, mode_t mode, dev_t dev) {
	return sys_mknod(pathname, mode, dev);
}
