#ifndef _SYS_BLOCK_H
#define _SYS_BLOCK_H

#include <sys/types.h>

// deprecated, use BLOCK_GET_DISK_INFO instead
#define BLOCK_GET_SIZE     17000

#define BLOCK_GET_DISK_INFO 17001
#define BLOCK_RESCAN_PARTS  17002
#define BLOCK_GET_PART_INFO 17003
#define BLOCK_OPEN_DISK     17004

typedef struct block_disk_info {
	char uuid[64];
	char partition_table_type[64];
	size_t logical_block_size;
	size_t blocks_count;
	char reserved[128];
} block_disk_info_t;

typedef struct block_part_info {
	char uuid[64];
	char fs_uuid[64];
	off_t offset;
	size_t size;
	char reserved[128];
} block_part_info_t;

#endif
