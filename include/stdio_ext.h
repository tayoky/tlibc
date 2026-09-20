#ifndef _STDIO_EXT_H
#define _STDIO_EXT_H

#include <stdio.h>

size_t __fbufsize(FILE *stream);
size_t __fpending(FILE *stream);
size_t __freadahead(FILE *stream);
int __freading(FILE *stream);
int __fwriting(FILE *stream);
void  __fpurge(FILE *stream);

#endif
