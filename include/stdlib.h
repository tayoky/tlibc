#ifndef STDLIB_H
#define STDLIB_H

#include <sys/types.h>
#include <sys/type.h> 

void exit(int status);

void *malloc(size_t amount);
void free(void *ptr);
void *calloc(size_t num,size_t size);
void *realloc(void *ptr,size_t new_size);

void abort(void);

//convertion things

long long int atoll(const char *str);
long int atol(const char *str);
int atoi(const char *str);
double atof(const char *str);

//environement varirables

int putenv(char *str);
char *getenv(const char *name);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#endif
