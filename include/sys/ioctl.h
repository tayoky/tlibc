#ifndef _SYS_IOCTL_H
#define _SYS_IOCTL_H

#include <abi/ioctl.h>
#include <sys/types.h>

int ioctl(int fd,unsigned long op,void *arg);

#endif
