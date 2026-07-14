#include <sysdeps.h>

TLIBC_WEAK int sys_getpeername(int socket, struct sockaddr *address, socklen_t *address_len) {
	return __set_errno(-ENOSYS);
}
