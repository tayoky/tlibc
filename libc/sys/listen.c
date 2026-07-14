#include <sys/socket.h>
#include <sysdeps.h>

int listen(int socket, int backlog) {
	return sys_listen(socket, backlog);
}
