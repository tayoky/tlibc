#include <sysdeps.h>

TLIBC_WEAK int sys_getsockname(int socket, struct sockaddr *address, socklen_t *address_len) {
	return __set_errno(-ENOSYS);
}
