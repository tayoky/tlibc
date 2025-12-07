#ifndef _SYS_UIO_H
#define _SYS_UIO_H

#include <sys/types.h>

struct iovec {
	void   *iov_base; // base address of a memory region for input or output
	size_t  iov_len;  // the size of the memory pointed to by iov_base
};

#endif