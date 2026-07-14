#include <sys/socket.h>
#include <sysdeps.h>

int shutdown(int socket, int how) {
	return sys_shutdown(socket, how);
}
