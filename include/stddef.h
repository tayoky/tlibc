#ifndef STDDEF_H
#define STDDEF_H



#ifndef NULL
#define NULL
#endif

#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef unsigned long size_t;
#endif

typedef signed long ptrdiff_t;

typedef char wchar_t;

//TODO : offsetof() macro

#endif
