#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

int vsprintf(char *buf, const char *fmt, va_list args) {
	return vsnprintf(buf, SIZE_MAX, fmt, args);
}
