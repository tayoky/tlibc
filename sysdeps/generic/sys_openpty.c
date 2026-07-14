#include <sysdeps.h>

TLIBC_WEAK int sys_openpty(int *amaster, int *aslave, char *name, const struct termios *termp, const struct winsize *winp) {
	return __set_errno(-ENOSYS);
}
