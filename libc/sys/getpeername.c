#include <sys/socket.h>
#include <sysdeps.h>

int getpeername(int socket, struct sockaddr *address, socklen_t *address_len) {
	return sys_getpeername(socket, address, address_len);
}
