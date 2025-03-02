#ifndef STDLIB_H
#define STDLIB_H

void exit(int status);

typedef unsigned long size_t;

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

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

#endif
