#ifndef _SYS_SYSMACROS_H
#define _SYS_SYSMACROS_H

#include <sys/types.h>
#include <limits.h>

#define __DEV_T_HALF (sizeof(dev_t) * CHAR_BIT / 2)
#define __DEV_T_MASK ((1ULL << __DEV_T_HALF) - 1)

static inline dev_t makedev(unsigned int maj, unsigned int min) {
	return ((dev_t)maj << __DEV_T_HALF) | min;
}

static inline unsigned int major(dev_t dev) {
	return (dev >> __DEV_T_HALF) & __DEV_T_MASK;
}
static inline unsigned int minor(dev_t dev) {
	return dev & __DEV_T_MASK;
}

#endif
