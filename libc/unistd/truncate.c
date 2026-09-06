#include <sysdeps.h>
#include <unistd.h>

int truncate(const char *path, off_t length) {
	return sys_truncate(path, length);
}
