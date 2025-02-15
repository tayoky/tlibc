#ifndef STDDEF_H
#define STDDEF_H



#ifndef NULL
#define NULL (void *)0
#endif

#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef unsigned long size_t;
#endif

typedef signed long ptrdiff_t;

typedef char wchar_t;

#define offsetof(struct_type,member) (size_t)&((struct struct_type *)0)->member

#endif
