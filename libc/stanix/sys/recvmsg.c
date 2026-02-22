#include <sys/socket.h>
#include <syscall.h>
#include <errno.h>

ssize_t recvmsg(int socket, struct msghdr *message, int flags) {
	return __set_errno(__syscall3(SYS_recvmsg, socket, (long)message, flags));
}
