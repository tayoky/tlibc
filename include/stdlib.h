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

//convertion things

long long int atoll(const char *str);
long int atol(const char *str);
int atoi(const char *str);
double atof(const char *str);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

#endif