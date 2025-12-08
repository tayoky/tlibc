#include <sys/socket.h>
#include <syscall.h>
#include <errno.h>

int getsockopt(int socket, int level, int option_name, void *option_value, socklen_t *option_len) {
	return __set_errno(__syscall5(SYS_getsockopt, socket, level, option_name, (long)option_value, (long)option_len));
}
