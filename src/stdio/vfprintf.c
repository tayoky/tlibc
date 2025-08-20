#include <stdio.h>
#include <stdarg.h>

#ifndef PRINTF_MAX
#define PRINTF_MAX 4096
#endif

int vfprintf(FILE *stream, const char *fmt, va_list args){
	char buf[PRINTF_MAX];
	int size = vsnprintf(buf,PRINTF_MAX,fmt,args);

	return fwrite(buf,size,1,stream);
}
