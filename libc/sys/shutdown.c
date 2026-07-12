#include <sys/socket.h>
#include <sysdeps.h>

int shutdown(int socket, int how) {
	return CALL_SYSDEP(sys_shutdown, (socket, how));
}
