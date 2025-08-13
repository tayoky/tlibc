#include <stdio.h>
#include <stdarg.h>


int vfprintf(FILE *stream, const char *fmt, va_list args){
	char buf[PRINTF_MAX];
	int size = vsnprintf(buf,PRINTF_MAX,fmt,args);

	return fwrite(buf,size,1,stream);
}
