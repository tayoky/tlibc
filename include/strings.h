#ifndef STRINGS_H
#define STRINGS_H

#include <sys/types.h>

int strcasecmp(const char *,const char *);
int strncasecmp(const char *,const char *,size_t);
int memcmp(const void *,const void *,size_t n);
void *memove(void *,const void *,size_t);
void *memset(void *,int,size_t);

#define bcmp memcmp

#define bcopy(src,dest,size) (void)memmove(dest,src,size)

#define bzero(mem,size) (void)memset(mem,0,size)

#endif
