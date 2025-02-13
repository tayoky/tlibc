#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>

#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef unsigned long long size_t;
#endif


int snprintf(char * str,size_t maxlen, const char *fmt,...);
int vsnprintf(char * buf,size_t maxlen, const char *fmt,va_list args);

#endif