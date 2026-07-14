#include <sys/socket.h>
#include <sysdeps.h>

int socket(int domain, int type, int protocol) {
	return sys_socket(domain, type, protocol);
}
