#include <sys/socket.h>
#include <syscall.h>
#include <errno.h>

int socket(int domain, int type, int protocol) {
	return __set_errno(__syscall3(SYS_socket, domain, type, protocol));
}
