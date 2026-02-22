#include <stdio.h>
#include <stdarg.h>

#ifndef PRINTF_MAX
#define PRINTF_MAX 4096
#endif

ssize_t __fileio_write(FILE *stream, const void *buf, size_t count);

int vfprintf(FILE *stream, const char *fmt, va_list args){
	char buf[PRINTF_MAX];
	int size = vsnprintf(buf,PRINTF_MAX,fmt,args);

	return __fileio_write(stream, buf, size);
}
