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

	if (sys_open) {
		return sys_open(pathname, flags, mode);
#ifdef AT_FDCWD
	} else if (sys_openat) {
		return sys_openat(AT_FDCWD, pathname, flags, mode);
#endif
	} else {
		return __set_errno(-ENOSYS);
	}
}
