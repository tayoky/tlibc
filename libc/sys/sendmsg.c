#include <sys/socket.h>
#include <sysdeps.h>

ssize_t sendmsg(int socket, const struct msghdr *message, int flags) {
	return sys_sendmsg(socket, message, flags);
}
