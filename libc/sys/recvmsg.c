#include <sys/socket.h>
#include <sysdeps.h>

ssize_t recvmsg(int socket, struct msghdr *message, int flags) {
	return CALL_SYSDEP(sys_recvmsg, (socket, message, flags));
}
