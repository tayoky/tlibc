#include <sys/socket.h>
#include <sysdeps.h>

int connect(int socket, const struct sockaddr *address, socklen_t address_len) {
	return sys_connect(socket, address, address_len);
}
