#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

int vsprintf(char * buf,const char *fmt,va_list args){
	return vsnprintf(buf,INT_MAX,fmt,args);
}
