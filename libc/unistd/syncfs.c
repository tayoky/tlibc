#include <sysdeps.h>
#include <unistd.h>

int syncfs(int fd) {
	return sys_syncfs(fd);
}
