#include <stdio.h>
#include <stdarg.h>

int asprintf(char **restrict strp, const char *restrict fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int ret = vasprintf(strp, fmt, args);
	va_end(args);
	return ret;
}
