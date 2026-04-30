#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#ifndef PRINTF_MAX
#define PRINTF_MAX 4096
#endif

int vdprintf(int fd, const char *fmt, va_list args) {
	char buf[PRINTF_MAX];
	int size = vsnprintf(buf, sizeof(buf), fmt, args);

	return write(fd, buf, size);
}
