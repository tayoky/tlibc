#ifndef _SYS_SYSMACROS_H
#define _SYS_SYSMACROS_H

#include <sys/types.h>

static inline dev_t makedev(unsigned int maj, unsigned int min) {
	return maj << 32 | min;
}

static inline unsigned int major(dev_t dev) {
	return (dev >> 32) & 0xffffffff;
}
static inline unsigned int minor(dev_t dev) {
	return dev & 0xffffffff;
}

#endif