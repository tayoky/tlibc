#include <sysdeps.h>
#include <termios.h>

TLIBC_WEAK int sys_isatty(int fd) {
	struct termios term;
	return tcgetattr(fd, &term) < 0 ? 0 : 1;
}
