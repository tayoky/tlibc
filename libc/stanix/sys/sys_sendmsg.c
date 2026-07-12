#include <sys/socket.h>
#include <errno.h>
#include <syscall.h>

ssize_t sendmsg(int socket, const struct msghdr *message, int flags) {
	return __set_errno(__syscall3(SYS_sendmsg, socket, (long)message, flags));
}
