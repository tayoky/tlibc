#ifndef _SYS_SOCKET_H
#define _SYS_SOCKET_H

#include <sys/types.h>
#include <sys/uio.h>

#define SOCK_STREAM    1
#define SOCK_DGRAM     2
#define SOCK_SEQPACKET 3
#define SOCK_RAW       4

typedef unsigned int sa_family_t;
typedef size_t socklen_t;

struct sockaddr {
	sa_family_t  sa_family;  // Address family
	char         sa_data[16];  // Socket address (variable-length data)
};

struct msghdr {
	void          *msg_name;       // optional address
	socklen_t      msg_namelen;    // size of address
	struct iovec  *msg_iov;        // scatter/gather array
	int            msg_iovlen;     // members in msg_iov
	void          *msg_control;    // ancillary data; see below
	socklen_t      msg_controllen; // ancillary data buffer len
	int            msg_flags;      // flags on received message.
};

#define AF_UNIX 3

#endif