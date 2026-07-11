#ifndef _FCNTL_H
#define _FCNTL_H

#include <abi/fcntl.h>
#include <sys/types.h>

int open(const char *pathname, int flags, ... /* mode_t mode */);
int creat(const char *pathname, mode_t mode);
int fcntl(int fd, int op, ... /* arg */);

// some stanix specific stuff
// TODO : hide this behind a macro
int fdname_r(int fd, char *buf, size_t size);
char *fdname(int fd);

#endif
