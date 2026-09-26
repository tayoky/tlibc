#ifndef _STDIO_H
#define _STDIO_H

#include <features.h>
#include <sys/types.h>
#include <stdarg.h>

//maybee should be equal to PATH_MAX from limits.h ???
#define FILENAME_MAX 256

typedef struct _FILE FILE;

#ifdef __TLIBC__
struct __fpos {
	size_t offset;
};
#else
// we want fpos_t to be opaque but apps need to know it's size
struct __fpos {
	long __padding[4];
};
#endif

typedef struct __fpos fpos_t;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

#define stdin  stdin
#define stdout stdout
#define stderr stderr

int vsnprintf(char *buf, size_t maxlen, const char *fmt, va_list args);
int vasprintf(char **restrict strp, const char *restrict fmt, va_list args);
int vdprintf(int fd, const char *fmt, va_list args);
int vfprintf(FILE *stream, const char *fmt, va_list args);

int sscanf(const char *buf, const char *fmt, ...);
int vsscanf(const char *buf, const char *fmt, va_list args);
int fscanf(FILE *stream, const char *fmt, ...);
int vfscanf(FILE *stream, const char *fmt, va_list args);
int vscanf(const char *fmt, va_list args);
int scanf(const char *fmt, ...);

#ifdef TLIBC_FAST_INLINES
static inline int sprintf(char *buf, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int ret = vsnprintf(buf, (size_t)-1, fmt, args);
	va_end(args);
	return ret;
}
static inline int vsprintf(char *buf, const char *fmt, va_list args) {
	return vsnprintf(buf, (size_t)-1, fmt, args);
}
static inline int snprintf(char *str, size_t maxlen, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int ret = vsnprintf(str, maxlen, fmt, args);
	va_end(args);
	return ret;
}
static inline int asprintf(char **restrict strp, const char *restrict fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int ret = vasprintf(strp, fmt, args);
	va_end(args);
	return ret;
}
static inline int dprintf(int fd, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int ret = vdprintf(fd, fmt, args);
	va_end(args);
	return ret;
}
static inline int fprintf(FILE *stream, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int ret = vfprintf(stream, fmt, args);
	va_end(args);
	return ret;
}
static inline int printf(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int ret = vfprintf(stdout, fmt, args);
	va_end(args);
	return ret;
}
static inline int vprintf(const char *fmt, va_list args) {
	return vfprintf(stdout, fmt, args);
}
#else
int sprintf(char *buf, const char *fmt, ...);
int vsprintf(char *buf, const char *fmt, va_list args);
int snprintf(char *str, size_t maxlen, const char *fmt, ...);
int asprintf(char **restrict strp, const char *restrict fmt, ...);
int dprintf(int fd, const char *fmt, ...);
int fprintf(FILE *stream, const char *fmt, ...);
int printf(const char *fmt, ...);
int vprintf(const char *fmt, va_list args);
#endif

FILE *fopen(const char *path, const char *mode);
FILE *freopen(const char *pathname, const char *mode, FILE *stream);
FILE *tmpfile(void);
FILE *open_memstream(char **ptr, size_t *sizeloc);
int fclose(FILE *stream);
size_t fread(void *ptr, size_t size, size_t n, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t n, FILE *stream);

#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE
FILE *fdopen(int handle, const char *type);
int fileno(FILE *stream);
#endif


//seek func
int fseek(FILE *stream, long offset, int origin);
long ftell(FILE *stream);
void rewind(FILE *stream);
int fgetpos(FILE *stream, fpos_t *pos);
int fsetpos(FILE *stream, fpos_t *pos);
#if (defined(_FILE_OFFSET_BITS) && _FILE_OFFSET_BITS == 64) ||(defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L)
int fseeko(FILE *stream, off_t offset, int origin);
off_t ftello(FILE *stream);
#endif

// put/get
int fgetc(FILE *stream);
char *fgets(char *string, int n, FILE *stream);
#ifndef __ISOC11_SOURCE
char *gets(char *buffer);
#endif
int fputc(int c, FILE *stream);
int fputs(const char *string, FILE *stream);
int puts(const char *string);
#ifdef TLIBC_FAST_INLINES
static inline int getc(FILE *stream) {
	return fgetc(stream);
}
static inline int getchar(void) {
	return fgetc(stdin);
}
static inline int putc(int c, FILE *stream) {
	return fputc(c, stream);
}
static inline int putchar(int c) {
	return fputc(c, stdout);
}
#else
int getc(FILE *stream);
int getchar(void);
int putc(int c, FILE *stream);
int putchar(int c);
#endif


// unlocked stdio
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 199309L
void flockfile(FILE *filehandle);
int ftrylockfile(FILE *filehandle);
void funlockfile(FILE *filehandle);

int getc_unlocked(FILE *stream);
int putc_unlocked(int c, FILE *stream);

#ifdef TLIBC_FAST_INLINES
static inline int getchar_unlocked(void) {
	return getc_unlocked(stdin);
}

static inline int putchar_unlocked(int c) {
	return putc_unlocked(c, stdout);
}
#else
int getchar_unlocked(void);
int putchar_unlocked(int c);
#endif
#endif

void clearerr(FILE *stream);
int feof(FILE *stream);
int ferror(FILE *stream);
void perror(const char *string);

int ungetc(int c, FILE *stream);

#define _IONBF 0
#define _IOFBF 1
#define _IOLBF 2

int fflush(FILE *stream);
int setvbuf(FILE *stream, char *buf, int type, size_t size);
void setbuf(FILE *stream, char *buf);

int rename(const char *oldpath, const char *newpath);
int remove(const char *pathname);

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
