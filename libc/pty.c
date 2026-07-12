#include <pty.h>
#include <sysdeps.h>

int openpty(int *amaster, int *aslave, char *name, const struct termios *termp, const struct winsize *winp) {
	return CALL_SYSDEP(sys_openpty, (amaster, aslave, name, termp, winp));
}
