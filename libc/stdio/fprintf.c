#include <stdarg.h>
#include <stdio.h>

int fprintf(FILE *stream, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int ret = vfprintf(stream, fmt, args);
	va_end(args);
	return ret;
}
