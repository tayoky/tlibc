#include <stdio.h>
#include <stdarg.h>

int snprintf(char * str,size_t maxlen, const char *fmt,...){
	va_list args;
	va_start(args,fmt);
	int ret = vsnprintf(str,maxlen,fmt,args);
	va_end(args);
	return ret;
}
