#ifndef POLL_H
#define POLL_H

struct pollfd {
	int   fd;      //file descriptor
	short events;  //requested events
	short revents; //returned events
};

typedef unsigned int nfds_t;

int poll(struct pollfd *fds, nfds_t nfds, int timeout);

#endif