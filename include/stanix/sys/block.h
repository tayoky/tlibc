#ifndef _SYS_BLOCK_H
#define _SYS_BLOCK_H

#include <sys/types.h>

// deprecated, use BLOCK_GET_TOPOLOGY instead
#define BLOCK_GET_SIZE     17000

#define BLOCK_GET_TOPOLOGY 17001
#define BLOCK_RESCAN_PARTS 17002

typedef struct block_topology {
	size_t logical_block_size;
	size_t blocks_count;
} block_topology_t;

#endif
