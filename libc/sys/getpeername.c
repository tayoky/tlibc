#include <sys/socket.h>
#include <sysdeps.h>

int getpeername(int socket, struct sockaddr *address, socklen_t *address_len) {
	return CALL_SYSDEP(sys_getpeername, (socket, address, address_len));
}
