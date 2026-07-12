#include <unistd.h>
#include <termios.h>
#include <sysdeps.h>

int isatty(int fd) {
	if (sys_isatty) {
		return sys_isatty(fd);
	} else {
		struct termios term;
		return tcgetattr(fd, &term) < 0 ? 0 : 1;
	}
}
