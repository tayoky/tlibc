#ifndef STDINT_H
#define STDINT_H

//signed
typedef signed char        int8_t;
typedef signed short       int16_t;
typedef signed int         int32_t;
typedef signed long long   int64_t;

//unsigned
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

//now least

//signed least
typedef signed char        int_least8_t;
typedef signed short       int_least16_t;
typedef signed int         int_least32_t;
typedef signed long long   int_least64_t;

//unsigned least
typedef unsigned char      uint_least8_t;
typedef unsigned short     uint_least16_t;
typedef unsigned int       uint_least32_t;
typedef unsigned long long uint_least64_t;

//now fast

//signed fast
typedef signed char        int8fast8_t;
typedef signed int         int8fast16_t;
typedef signed int         int8fast32_t;
typedef signed long long   int8fast64_t;

//unsigned fast
typedef unsigned char      uint_fast8_t;
typedef unsigned int       uint_fast16_t;
typedef unsigned int       uint_fast32_t;
typedef unsigned long long uint_fast64_t;

//max
typedef int64_t  int_max;
typedef uint64_t uint_max;


//ptr
#ifdef i386
typedef signed   int intptr_t;
typedef unsigned int uintptr_t;
#else
typedef signed   long intptr_t;
typedef unsigned long uintptr_t;
#endif

#endif