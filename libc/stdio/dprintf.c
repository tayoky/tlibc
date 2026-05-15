#include <stdarg.h>
#include <stdio.h>

int dprintf(int fd, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int ret = vdprintf(fd, fmt, args);
	va_end(args);
	return ret;
}
