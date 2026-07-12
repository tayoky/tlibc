#include <errno.h>
#include <fcntl.h>
#include <sysdeps.h>
#include <syscall.h>

int sys_fcntl(int fd, int op, va_list args) {
	int arg = 0;
	if (op == F_SETFD || op == F_DUPFD) {
		arg = va_arg(args, int);
	}

	return __set_errno(__syscall3(SYS_fcntl, fd, op, arg));
}
