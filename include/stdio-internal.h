#ifndef _STDIO_INTERNAL_H
#define _STDIO_INTERNAL_H

#include <sys/types.h>
#include <sysdeps.h>
#include <stdio.h>

struct _FILE{
	struct _FILE *next;
	struct _FILE *prev;
	char *buf;
	size_t buf_size;
	char *read_end;
	char *read_pos;
	char *write_pos;
	char *write_end;
	unsigned long error;
	int fd;
	int eof;
	int unget;
	int buftype;
	int internalbuf;
	futex_atomic_t thread;
	size_t lock_count;
};

ssize_t __do_write(FILE *stream, const char *buf, size_t count);
ssize_t __fileio_read(FILE *stream, void *buf, size_t count);
ssize_t __fileio_read_unlocked(FILE *stream, void *buf, size_t count);
ssize_t __fileio_write(FILE *stream, const void *buf, size_t count);
ssize_t __fileio_write_unlocked(FILE *stream, const void *buf, size_t count);

#endif
