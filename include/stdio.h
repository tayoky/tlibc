#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>

#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef unsigned long long size_t;
#endif


int snprintf(char * str,size_t maxlen, const char *fmt,...);
int vsnprintf(char * buf,size_t maxlen, const char *fmt,va_list args);

struct _FILE;
typedef struct _FILE FILE;

FILE *fopen(const char *path,const char *mode);
int fclose(FILE *stream);
size_t fread(void * ptr, size_t size, size_t n, FILE *stream);
size_t fwrite(void * ptr, size_t size, size_t n, FILE *stream);

int fprintf(FILE *stream, const char *fmt, ...);
int vfprintf(FILE *stream, const char *fmt, va_list args);

int printf(const char *fmt, ...);
int vprintf(const char *fmt, va_list args);

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

#define PRINTF_MAX 1024

#endif