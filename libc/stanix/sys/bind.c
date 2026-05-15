#include <sys/socket.h>
#include <errno.h>
#include <syscall.h>

int bind(int socket, const struct sockaddr *address, socklen_t address_len) {
	return __set_errno(__syscall3(SYS_bind, socket, (long)address, address_len));
}
