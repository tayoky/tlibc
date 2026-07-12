#include <sys/socket.h>
#include <sysdeps.h>

int socket(int domain, int type, int protocol) {
	return CALL_SYSDEP(sys_socket, (domain, type, protocol));
}
