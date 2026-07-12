#include <sys/socket.h>
#include <sysdeps.h>
#include <errno.h>
#include <syscall.h>

int sys_connect(int socket, const struct sockaddr *address, socklen_t address_len) {
	return __set_errno(__syscall3(SYS_connect, socket, (long)address, address_len));
}
