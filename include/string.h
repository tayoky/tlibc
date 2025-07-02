#ifndef STRING_H
#define STRING_H

#include <sys/types.h>

//str
char *strcat(char * dest, const char * src);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src,size_t n);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *str1,const  char *str2,size_t n);
char *strchr(const char *str, int c);
char *strrchr(const char *str, int c);
char *strpbrk(const char *str,const char *search);
char *strstr(const char *str1,const char *str2);
size_t strcspn(const char *str, const char *rej);
int strcasecmp(const char *str1, const char *str2);
int strncasecmp(const char *str1, const char *str2, size_t n);

size_t strlen(const char *str);

char *strdup(const char *str);
char *strndup(const char *str,size_t count);

//mem
void *memset(void *pointer,int value,size_t count);
void *memcpy(void *dest, const void *src,size_t n);
int memcmp(const void *buf1,const void *buf2,size_t count);
void *memmove(void *dest, const void *src, size_t n);
void *memchr(const void *buf, int c, size_t count);

const char *strerror(int errnum);


#ifndef NULL
#define NULL (void *)0
#endif
#endif
