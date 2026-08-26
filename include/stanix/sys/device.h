#ifndef _SYS_DEVICE_H
#define _SYS_DEVICE_H

#include <sys/ioctl.h>

typedef struct device_info {
	char product[256];
	char firmware[256];
	char vendor[256];
	char setial[256];
} device_info_t;

#define DEVICE_GET_INFO 19000

#endif
