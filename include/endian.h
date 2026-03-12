#ifndef _ENDIAN_H
#define _EDNIAN_H

#include <stdint.h>

#ifndef __ORDER_LITTLE_ENDIAN__
#define __ORDER_LITTLE_ENDIAN__ 0
#endif

#ifndef __ORDER_BIG_ENDIAN__
#define __ORDER_BIG_ENDIAN__ 1
#endif

#ifndef __BYTE_ORDER__
#if defined(__x86_64__) || defined(__i386__) || defined(__aarch64__)
#define __BYTE_ORDER__ __ORDER_LITTLE_ENDIAN__
#else
#error do not know endian for this arch
#endif
#endif

#define LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
#define BIG_ENDIAN __ORDER_BIG_ENDIAN__
#define BYTE_ORDER __BYTE_ORDER__

#endif
