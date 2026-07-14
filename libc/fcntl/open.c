#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include <sysdeps.h>

int open(const char *pathname, int flags, ... /* mode_t mode */) {
	mode_t mode = 0;
	if (flags & O_CREAT) {
		va_list args;
		va_start(args, flags);
		mode = va_arg(args, mode_t);
		va_end(args);
	}

	return sys_open(pathname, flags, mode);
}
