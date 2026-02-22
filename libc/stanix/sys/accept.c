#include <sys/socket.h>
#include <syscall.h>
#include <errno.h>

int accept(int socket, struct sockaddr *address, socklen_t *address_len) {
	return __set_errno(__syscall3(SYS_accept, socket, (long)address, (long)address_len));
}
