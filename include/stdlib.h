#ifndef _STDLIB_H
#define _STDLIB_H

#include <alloca.h>
#include <tlibcnoreturn.h>
#include <stddef.h>
#include <limits.h>

int rand(void);
int rand_r(unsigned int *seedp);
void srand(unsigned int seed);

#define RAND_MAX INT_MAX

TLIBC_NORETURN void _Exit(int status);
TLIBC_NORETURN void exit(int status);
int atexit(void (*func)(void));

void *malloc(size_t amount);
void free(void *ptr);
void *calloc(size_t num, size_t size);
int posix_memalign(void **memptr, size_t alignment, size_t size);
void *aligned_alloc(size_t alignment, size_t size);
void *realloc(void *ptr, size_t new_size);

void abort(void);

//convertion things

long long int atoll(const char *str);
long int atol(const char *str);
int atoi(const char *str);
double atof(const char *str);

#define strto(type,name) type name(const char *str, char **end,int base);
strto(long, strtol)
strto(long long, strtoll)
strto(unsigned long, strtoul)
strto(unsigned long long, strtoull)
#undef strto
#define strtd(type,name) type name(const char *str, char **end);
strtd(float, strtof)
strtd(double, strtod)
strtd(long double, strtold)
#undef strtd

// math stuff

typedef struct {
    int quot;
    int rem;
} div_t;

typedef struct {
    long quot;
    long rem;
} ldiv_t;

typedef struct {
    long long quot;
    long long rem;
} lldiv_t;
div_t div(int number, int denom);
ldiv_t ldiv(long number, long denom);
lldiv_t lldiv(long long number, long long denom);
int abs(int);
long labs(long);
long long llabs(long long);
void qsort_r(void *base, size_t n, size_t size, int (*compar)(const void *, const void *, void *), void *arg);
void qsort(void *base, size_t n, size_t size, int (*compar)(const void *, const void *));
void *bsearch(const void *key, const void *base, size_t n, size_t size, int (*compar)(const void *, const void *));

char *realpath(const char *path, char *resolved_path);

//environement variables

int putenv(char *str);
char *getenv(const char *name);
int setenv(const char *name, const char *value, int overwrite);
int unsetenv(const char *name);
extern char **environ;

int system(const char *command);

//tmp files
#ifdef __cplusplus
// template is a keyword in c++
int mkostemp(char *_template, int flags);
int mkstemp(char *_template);
int mkstemp(char *_template);
#else
int mkostemp(char *template, int flags);
int mkstemp(char *template);
int mkstemp(char *template);
#endif

//wchar conversion
int mbtowc(wchar_t *pwcs, const char *str, size_t n);
size_t mbstowcs(wchar_t *pwcs, const char *str, size_t n);
int mblen(const char *str, size_t n);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#endif
