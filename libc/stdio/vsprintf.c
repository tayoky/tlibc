#include <stdarg.h>
#include <stdio.h>
#include <limits.h>

int vsprintf(char *buf, const char *fmt, va_list args) {
	return vsnprintf(buf, SIZE_MAX, fmt, args);
}
