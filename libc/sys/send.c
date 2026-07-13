#include <sys/socket.h>
#include <stddef.h>

ssize_t send(int socket, const void *buffer, size_t length, int flags) {
	struct iovec vec = {
		.iov_base = (void *)buffer,
		.iov_len = length,
	};
	struct msghdr msg = {
		.msg_name = NULL,
		.msg_namelen = 0,
		.msg_iov = &vec,
		.msg_iovlen = 1,
	};
	return sendmsg(socket, &msg, flags);
}
