#include <unistd.h>
#include <sysdeps.h>

int close(int fd) {
	return sys_close(fd);
}
