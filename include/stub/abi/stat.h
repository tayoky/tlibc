#ifndef _ABI_STAT_H
#define _ABI_STAT_H

// Stub stat ABI

#include <sys/types.h>

struct stat {
	dev_t     st_dev;      // ID of device containing file
	ino_t     st_ino;      // file serial number
	mode_t    st_mode;     // mode of file (see below)
	nlink_t   st_nlink;    // number of links to the file
	uid_t     st_uid;      // user ID of file
	gid_t     st_gid;      // group ID of file
	dev_t     st_rdev;     // device ID (if file is character or block special)
	off_t     st_size;     // file size in bytes (if file is a regular file)
	time_t    st_atime;    // time of last access
	time_t    st_mtime;    // time of last data modification
	time_t    st_ctime;    // time of last status change
	blksize_t st_blksize;  // a filesystem-specific preferred I/O block size for
	blkcnt_t  st_blocks;   // number of blocks allocated for this object
};

#endif
