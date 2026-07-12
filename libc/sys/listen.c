#include <sys/socket.h>
#include <sysdeps.h>

int listen(int socket, int backlog) {
	return CALL_SYSDEP(sys_listen, (socket, backlog));
}
