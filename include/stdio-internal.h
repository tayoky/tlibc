#ifndef _STDIO_INTERNAL_H
#define _STDIO_INTERNAL_H

#include <sys/types.h>
#include <stdio.h>

struct _FILE{
	struct _FILE *next;
	struct _FILE *prev;
	char *buf;
	size_t bufsize;
	size_t usedsize;
	unsigned long error;
	int fd;
	int eof;
	int unget;
	int buftype;
	int internalbuf;
};

ssize_t __fileio_read(FILE *stream, void *buf, size_t count);
ssize_t __fileio_write(FILE *stream, const void *buf, size_t count);

#endif
