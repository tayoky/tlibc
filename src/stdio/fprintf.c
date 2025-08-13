#include <stdio.h>
#include <stdarg.h>

int fprintf(FILE *stream, const char *fmt, ...){
	va_list args;
	va_start(args,fmt);
	int ret = vfprintf(stream,fmt,args);
	va_end(args);
	return ret;
}
