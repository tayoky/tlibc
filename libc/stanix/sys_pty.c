#include <errno.h>
#include <pty.h>
#include <sysdeps.h>
#include <syscall.h>

int sys_openpty(int *amaster, int *aslave, char *name, const struct termios *termp, const struct winsize *winp) {
	return __set_errno(__syscall5(SYS_openpty, (long)amaster, (long)aslave, (long)name, (long)termp, (long)winp));
}
