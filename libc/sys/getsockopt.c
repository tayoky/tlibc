#include <sys/socket.h>
#include <sysdeps.h>

int getsockopt(int socket, int level, int option_name, void *option_value, socklen_t *option_len) {
	return CALL_SYSDEP(sys_getsockopt, (socket, level, option_name, option_value, option_len));
}
