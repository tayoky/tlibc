#ifndef STRING_H
#define STRING_H

#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef unsigned long long size_t;
#endif

char *strcpy(char *dest, const char *src);

size_t strlen(const char *str);

void *memset(void *pointer,int value,size_t count);

int strcmp(const char *s1, const char *s2);

char *strdup(const char *str);

char *strcat(char * dest, const char * src);

void *memcpy(void *dest, const void *src,size_t n);

int memcmp(const void *buf1,const void *buf2,size_t count);
#endif