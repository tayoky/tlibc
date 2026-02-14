#ifndef _STRINGS_H
#define _STRINGS_H

#include <sys/types.h>

int strcasecmp(const char *,const char *);
int strncasecmp(const char *,const char *,size_t);
int memcmp(const void *,const void *,size_t n);
void *memove(void *,const void *,size_t);
void *memset(void *,int,size_t);

static inline int bcmp(const void *b1, const void *b2, size_t n) {
	return memcmp(b1, b2, n);
}

static inline void bcopy(const void *src, void *dest, size_t n) {
	memmove(dest, src, n);
}

static inline void bzero(void *dest, size_t n) {
	memset(dest, 0, n);
}

#endif
