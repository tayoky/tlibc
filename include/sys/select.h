#ifndef _SYS_SELECT_H
#define _SYS_SELECT_H

#include <sys/time.h>
#include <stdint.h>

#define FD_SETSIZE 1024

typedef struct __fd_set {
	uint32_t data[FD_SETSIZE/32];
} fd_set;

int select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds,
                  fd_set *restrict exceptfds, struct timeval *restrict timeout);

void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, const fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);

#endif
