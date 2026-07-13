#include <sys/socket.h>

ssize_t sendto(int socket, const void *buffer, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len) {
	struct iovec vec = {
		.iov_base = (void *)buffer,
		.iov_len = length,
	};
	struct msghdr msg = {
		.msg_name = (struct sockaddr *)dest_addr,
		.msg_namelen = dest_len,
		.msg_iov = &vec,
		.msg_iovlen = 1,
	};
	return sendmsg(socket, &msg, flags);
}
