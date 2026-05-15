#include <sys/socket.h>
#include <errno.h>
#include <syscall.h>

int getsockname(int socket, struct sockaddr *address, socklen_t *address_len) {
	return __set_errno(__syscall3(SYS_getsockname, socket, (long)address, (long)address_len));
}
