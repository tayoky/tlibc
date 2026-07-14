#include <unistd.h>
#include <sysdeps.h>

int unlink(const char *pathname) {
	return sys_unlink(pathname);
}
