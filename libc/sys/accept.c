#include <sys/socket.h>
#include <sysdeps.h>

int accept(int socket, struct sockaddr *address, socklen_t *address_len) {
	return CALL_SYSDEP(sys_accept, (socket, address, address_len));
}
