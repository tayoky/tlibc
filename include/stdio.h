#ifndef STDIO_H
#define STDIO_H

#include <sys/types.h>
#include <stdarg.h>


struct _FILE{
	int fd;
	unsigned long errno;
	int eof;
	int unget;
};
typedef struct _FILE FILE;

typedef size_t fpos_t;

int sprintf(char * str,const char *fmt,...);
int vsprintf(char * buf,const char *fmt,va_list args);
int snprintf(char * str,size_t maxlen, const char *fmt,...);
int vsnprintf(char * buf,size_t maxlen, const char *fmt,va_list args);

int sscanf(const char *buf,const char *fmt,...);
int vsscanf(const char *buf,const char *fmt,va_list args);
int fscanf(FILE *stream,const char *fmt,...);
int vfscanf(FILE *stream,const char *fmt,va_list args);


FILE *fopen(const char *path,const char *mode);
int fclose(FILE *stream);
size_t fread(void * ptr, size_t size, size_t n, FILE *stream);
size_t fwrite(const void * ptr, size_t size, size_t n, FILE *stream);

int fprintf(FILE *stream, const char *fmt, ...);
int vfprintf(FILE *stream, const char *fmt, va_list args);

int printf(const char *fmt, ...);
int vprintf(const char *fmt, va_list args);

FILE *fdopen(int handle,const char *type);
FILE *tmpfile(void);
int fileno(FILE *stream);

//seek func
int fseek(FILE *stream, long int offset, int origin);
long int ftell(FILE *stream);
void rewind(FILE *stream);

//put/get
int fgetc(FILE *stream);
int getc(FILE *stream);
int getchar(void);
char *fgets (char *string, int n, FILE *stream);
char *gets(char *buffer);
int fputc(int c,FILE *stream);
int putc(int c,FILE *stream);
int putchar(int c);
int fputs(const char *string,FILE *stream);
int puts(const char *string);

void clearerr(FILE *stream);
int feof(FILE *stream);
int ferror(FILE *stream);
void perror(const char *string);

int ungetc(int c,FILE *stream);

int fflush(FILE *stream);

int remove(const char *pathname);

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

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

#define EOF -1

#endif
