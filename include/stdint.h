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
#ifndef INTPTR_T_DEFINED
#define INTPTR_T_DEFINED
typedef int64_t  intptr_t;
#endif

typedef uint64_t uintptr_t;

#define CHAR_BIT 8

#define SCHAR_MIN -128
#define SCHAR_MAX 127
#define UCHAR_MAX 0xFF

#define INT_MIN -2147483648
#define INT_MAX 2147483647
#define UINT_MAX 0xFFFFFFFF

#define SHRT_MIN -32768
#define SHRT_MAX 32767
#define USHRT_MAX 0xFFFF

#define LONG_MIN -9223372036854775808
#define LONG_MAX 9223372036854775807
#define ULONG_MAX 0xFFFFFFFFFFFFFFFF

#endif