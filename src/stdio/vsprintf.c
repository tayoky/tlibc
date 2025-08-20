#include <stdio.h>
#include <stdarg.h>

int vsprintf(char * buf,const char *fmt,va_list args){
	return vsnprintf(buf,0,fmt,args);
}
