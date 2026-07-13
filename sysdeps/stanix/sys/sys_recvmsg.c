#include <sys/socket.h>
#include <sysdeps.h>
#include <errno.h>
#include <syscall.h>

ssize_t sys_recvmsg(int socket, struct msghdr *message, int flags) {
	return __set_errno(__syscall3(SYS_recvmsg, socket, (long)message, flags));
}
