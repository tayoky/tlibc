#include <unistd.h>
#include <termios.h>
#include <sysdeps.h>

int isatty(int fd) {
	return sys_isatty(fd);
}
