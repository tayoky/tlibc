#include <sys/socket.h>
#include <syscall.h>
#include <errno.h>

int shutdown(int socket, int how) {
	return __set_errno(__syscall2(SYS_shutdown, socket, how));
}
