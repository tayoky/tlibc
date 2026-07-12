#include <fcntl.h>
#include <stdarg.h>
#include <sysdeps.h>

int fcntl(int fd, int op, ... /* arg */) {
	va_list args;
	va_start(args, op);
	int ret = CALL_SYSDEP(sys_fcntl, (fd, op, args));
	va_end(args);
	return ret;
}
