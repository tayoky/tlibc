#include <sys/socket.h>
#include <errno.h>
#include <syscall.h>

int setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len) {
	return __set_errno(__syscall5(SYS_setsockopt, socket, level, option_name, (long)option_value, option_len));
}
