#include <sys/socket.h>

ssize_t recvfrom(int socket, void *buffer, size_t length, int flags, struct sockaddr *address, socklen_t *address_len) {
	struct iovec vec = {
		.iov_base = buffer,
		.iov_len = length,
	};
	struct msghdr msg = {
		.msg_name = address,
		.msg_namelen = address_len ? *address_len : 0,
		.msg_iov = &vec,
		.msg_iovlen = 1,
	};
	ssize_t ret = recvmsg(socket, &msg, flags);
	if (address_len) *address_len = msg.msg_namelen;
	return ret;
}
