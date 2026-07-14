#include <sys/socket.h>
#include <sysdeps.h>

int bind(int socket, const struct sockaddr *address, socklen_t address_len) {
	return sys_bind(socket, address, address_len);
}
