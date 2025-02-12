#ifndef STDARG_H
#define STDARG_H

#define va_start(v,arg) __builtin_va_start(v,arg)
#define va_end(v)	__builtin_va_end(v)
#define va_arg(v,t)	__builtin_va_arg(v,t)
#define va_copy(d,s)	__builtin_va_copy(d,s)

typedef __builtin_va_list va_list;

#endif