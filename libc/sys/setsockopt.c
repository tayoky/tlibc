#include <sys/socket.h>
#include <sysdeps.h>

int setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len) {
	return sys_setsockopt(socket, level, option_name, option_value, option_len);
}
