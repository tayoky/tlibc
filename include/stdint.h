//stdint.h implementation by tayoky
//this implementation rely on __SIZEOF_XXX macro being defined by the compilator
#ifndef STDINT_H
#define STDINT_H

#ifndef __CHAR_BIT__
#define __CHAR_BIT__ 8
#endif

//start by finding ths standar type size
#define ___CHAR_BITS __CHAR_BIT__
#define ___SHRT_BITS __SIZEOF_SHORT__ * __CHAR_BIT__
#define ___INT_BITS  __SIZEOF_INT__  * __CHAR_BIT__
#define ___LONG_BITS __SIZEOF_LONG__ * __CHAR_BIT__
#define ___LONG_LONG_BITS __SIZEOF_LONG_LONG__ * __CHAR_BIT__

#define DEF_INTX(type,x) \
	typedef   signed type int##x##_t;\
	typedef unsigned type uint##x##_t;
#define DEF_LINTX(type,x) \
	typedef   signed type int_least##x##_t;\
	typedef unsigned type uint_least##x##_t;

//int8_t typedef
#if ___CHAR_BITS == 8
#define __int8_t_defined 1
DEF_INTX(char,8)
#elif ___SHRT_BITS == 8
#define __int8_t_defined 1
DEF_INTX(short,8)
#elif ___INT_BITS == 8
#define __int8_t_defined 1
DEF_INTX(int,8)
#elif ___LONG_BITS == 8
#define __int8_t_defined 1
DEF_INTX(long,8)
#elif ___LONG_LONG_BITS == 8
#define __int8_t_defined 1
DEF_INTX(long long,8)
#endif

//int16_t typedef
#if ___CHAR_BITS == 16
#define __int16_t_defined 1
DEF_INTX(char,16)
#elif ___SHRT_BITS == 16
#define __int16_t_defined 1
DEF_INTX(short,16)
#elif ___INT_BITS == 16
#define __int16_t_defined 1
DEF_INTX(int,16)
#elif ___LONG_BITS == 16
#define __int16_t_defined 1
DEF_INTX(long,16)
#elif ___LONG_LONG_BITS == 16
#define __int16_t_defined 1
DEF_INTX(long long,16)
#endif

//int32_t typedef
#if ___CHAR_BITS == 32
#define __int32_t_defined 1
DEF_INTX(char,32)
#elif ___SHRT_BITS == 32
#define __int32_t_defined 1
DEF_INTX(short,32)
#elif ___INT_BITS == 32
#define __int32_t_defined 1
DEF_INTX(int,32)
#elif ___LONG_BITS == 32
#define __int32_t_defined 1
DEF_INTX(long,32)
#elif ___LONG_LONG_BITS == 32
#define __int32_t_defined 1
DEF_INTX(long long,32)
#endif

//int64_t typedef
#if ___CHAR_BITS == 64
#define __int64_t_defined 1
DEF_INTX(char,64)
#elif ___SHRT_BITS == 64
#define __int64_t_defined 1
DEF_INTX(short,64)
#elif ___INT_BITS == 64
#define __int64_t_defined 1
DEF_INTX(int,64)
#elif ___LONG_BITS == 64
#define __int64_t_defined 1
DEF_INTX(long,64)
#elif ___LONG_LONG_BITS == 64
#define __int64_t_defined 1
DEF_INTX(long long,64)
#endif

//now least

///int_least8_t typedef
#if ___CHAR_BITS >= 8
#define __int_least8_t_defined 1
DEF_LINTX(char,8)
#elif ___SHRT_BITS >= 8
#define __int_least8_t_defined 1
DEF_LINTX(short,8)
#elif ___INT_BITS >= 8
#define __int_least8_t_defined 1
DEF_LINTX(int,8)
#elif ___LONG_BITS >= 8
#define __int_least8_t_defined 1
DEF_LINTX(long,8)
#elif ___LONG_LONG_BITS >= 8
#define __int_least8_t_defined 1
DEF_LINTX(long long,8)
#endif

//signed least
typedef signed short       int_least16_t;
typedef signed int         int_least32_t;
typedef signed long long   int_least64_t;

//unsigned least
typedef unsigned short     uint_least16_t;
typedef unsigned int       uint_least32_t;
typedef unsigned long long uint_least64_t;

//now fast

//signed fast
typedef signed char        int_fast8_t;
typedef signed int         int_fast16_t;
typedef signed int         int_fast32_t;
typedef signed long long   int_fast64_t;

//unsigned fast
typedef unsigned char      uint_fast8_t;
typedef unsigned int       uint_fast16_t;
typedef unsigned int       uint_fast32_t;
typedef unsigned long long uint_fast64_t;


typedef int64_t  intmax_t;
typedef uint64_t uintmax_t;

//ptr
//TODO : find the size of a pointer
//and find a standard type with at least the same size
typedef signed   long intptr_t;
typedef unsigned long uintptr_t;


//define limits
#ifdef __int8_t_defined
#define INT8_MAX 127
#define INT8_MIN -128
#define UINT8_MAX 0xff
#endif
#ifdef __int16_t_defined
#define INT16_MAX 0x7fff
#define INT16_MIN -INT16_MAX - 1
#define UINT16_MAX 0xffff
#endif
#ifdef __int32_t_defined
#define INT32_MAX 0x7fffffff
#define INT32_MIN -INT32_MAX - 1
#define UINT32_MAX 0xffffffff
#endif
#ifdef __int64_t_defined
#define INT64_MAX 0x7fffffffffffffff
#define INT64_MIN -INT64_MAX - 1
#define UINT64_MAX 0xffffffffffffffff
#endif


#endif
