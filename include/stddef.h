#ifndef STDDEF_H
#define STDDEF_H

#include <sys/types.h>

#ifndef NULL
#define NULL (void *)0
#endif

typedef signed long ptrdiff_t;

typedef char wchar_t;

#define offsetof(struct_type,member) (size_t)&((struct struct_type *)0)->member

#endif
