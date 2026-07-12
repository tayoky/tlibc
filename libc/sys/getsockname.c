#include <sys/socket.h>
#include <sysdeps.h>

int getsockname(int socket, struct sockaddr *address, socklen_t *address_len) {
	return CALL_SYSDEP(sys_getsockname, (socket, address, address_len));
}
