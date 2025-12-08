#include <sys/socket.h>
#include <syscall.h>
#include <errno.h>

ssize_t sendmsg(int socket, const struct msghdr *message, int flags) {
	return __set_errno(__syscall3(SYS_sendmsg, socket, (long)message, flags));
}
