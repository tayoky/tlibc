#include <sys/socket.h>
#include <sysdeps.h>
#include <errno.h>
#include <syscall.h>

int sys_socket(int domain, int type, int protocol) {
	return __set_errno(__syscall3(SYS_socket, domain, type, protocol));
}
