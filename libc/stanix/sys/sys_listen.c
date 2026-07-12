#include <sys/socket.h>
#include <errno.h>
#include <syscall.h>

int listen(int socket, int backlog) {
	return __set_errno(__syscall2(SYS_listen, socket, backlog));
}
