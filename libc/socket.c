#include <sys/socket.h>
#include <stddef.h>

ssize_t recv(int socket, void *buffer, size_t length, int flags) {
    struct iovec vec = {
        .iov_base = buffer,
        .iov_len  = length,
    };
    struct msghdr msg = {
        .msg_name    = NULL,
        .msg_namelen = 0,
        .msg_iov     = &vec,
        .msg_iovlen  = 1,
    };
    return recvmsg(socket, &msg, flags);

}

ssize_t recvfrom(int socket, void *buffer, size_t length, int flags, struct sockaddr *address, socklen_t *address_len) {
    struct iovec vec = {
        .iov_base = buffer,
        .iov_len  = length,
    };
    struct msghdr msg = {
        .msg_name    = address,
        .msg_namelen = address_len ? *address_len : 0,
        .msg_iov     = &vec,
        .msg_iovlen  = 1,
    };
    ssize_t ret = recvmsg(socket, &msg, flags);
    if (address_len) *address_len = msg.msg_namelen;
    return ret;
}

ssize_t send(int socket, const void *buffer, size_t length, int flags) {
    struct iovec vec = {
        .iov_base = (void*)buffer,
        .iov_len  = length,
    };
    struct msghdr msg = {
        .msg_name    = NULL,
        .msg_namelen = 0,
        .msg_iov     = &vec,
        .msg_iovlen  = 1,
    };
    return sendmsg(socket, &msg, flags);
}

ssize_t sendto(int socket, const void *buffer, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len) {
    struct iovec vec = {
        .iov_base = (void*)buffer,
        .iov_len  = length,
    };
    struct msghdr msg = {
        .msg_name    = (struct sockaddr*)dest_addr,
        .msg_namelen = dest_len,
        .msg_iov     = &vec,
        .msg_iovlen  = 1,
    };
    return sendmsg(socket, &msg, flags);
}
