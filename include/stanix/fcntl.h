#ifndef FCNTL_H
#define FCNTL_H

#include <sys/type.h>
#include <sys/types.h>

#define O_RDONLY	0x0000000 //open for read only
#define O_WRONLY	0x0000001 //open for write only
#define O_RDWR		0x0000002 //open for both read and write
#define O_CREAT		0x0000010 //create the file if it don't exist
#define O_EXCL		0x0000020 //trigger an error if can't create the file
#define O_NOCTTY	0x0000040 //if open tty don't make it the controlling tty
#define O_TRUNC		0x0000080 //truncate the file to be empty
#define O_APPEND	0x0000100 //go to the end of the file before each write
#define	O_NONBLOCK	0x0000200 //don't block on read/write
#define O_DIRECTORY	0x0000400 //must be a directory
#define O_CLOEXEC	0x0000800 //set close_on_exec
#define O_NOFOLLOW	0x0001000 //don't follow links


int open(const char *pathname, int flags, ... /* mode_t mode */ );
int creat(const char *pathname, mode_t mode);

#endif