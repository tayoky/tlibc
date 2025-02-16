#ifndef STDLIB_H
#define STDLIB_H

void exit(int status);

#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef unsigned long long size_t;
#endif

void *malloc(size_t amount);
void free(void *ptr);

void abort(void);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

#endif