#ifndef STRING_H
#define STRING_H

#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef unsigned long long size_t;
#endif

//str

char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src,size_t n);

size_t strlen(const char *str);

int strcmp(const char *s1, const char *s2);
int strncmp(const char *str1,const  char *str2,size_t n);

char *strrchr(const char *str, int c);

char *strcat(char * dest, const char * src);

char *strdup(const char *str);

int stricmp(const char *str1, const char *str2);

#define strcmpi(str1,str2) stricmp(str1,str2);

int strnicmp(const char *str1, const char *str2, size_t n);

#define strncmpi(str1,str2,n) strnicmp(str1,str2,n)

//mem

void *memset(void *pointer,int value,size_t count);

void *memcpy(void *dest, const void *src,size_t n);

int memcmp(const void *buf1,const void *buf2,size_t count);

void *memchr(const void *buf, int c, size_t count);

const char *strerror(int errnum);

#ifndef NULL
#define NULL (void *)0
#endif
#endif