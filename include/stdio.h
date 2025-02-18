#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>

#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef unsigned long long size_t;
#endif

#ifndef FPOS_T_DEFINED
#define FPOS_T_DEFNIED
typedef unsigned long long fpos_t;
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

FILE *fdopen(int handle, char *type);

//seek func
int fseek(FILE *stream, long int offset, int origin);
long int ftell(FILE *stream);
void rewind(FILE *stream);

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

//put/get
int fgetc(FILE *stream);
int getc(FILE *stream);
int getchar(void);

char *fgets (char *string, int n, FILE *stream);
char *gets(char *buffer);

int fputc(int c,FILE *stream);
int putc(int c,FILE *stream);
int putchar(int c);

int fputs (char *string, int n, FILE *stream);
int puts(char *string);

int feof(FILE *stream);

#define PRINTF_MAX 1024

#ifndef SEEK_SET
#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif
#ifndef SEEK_END
#define SEEK_END 2
#endif

#ifndef NULL
#define NULL (void *)0
#endif

#ifndef BUFSIZ
#define BUFSIZ 4096
#endif

#define EOF -1000

#endif
