#ifndef _ABI_DIRENT_H
#define _ABI_DIRENT_H

// Stub dirent ABI

#include <sys/types.h>

struct dirent {
	char d_name[256];
	ino_t d_ino; 
	int d_type;
};

#define DT_UNKNOWN  0
#define DT_REG      1
#define DT_DIR      2
#define DT_FIFO     3
#define DT_SOCK     4
#define DT_CHR      5
#define DT_BLK      6
#define DT_LNK      7

#endif
