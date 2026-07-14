#include <sysdeps.h>

TLIBC_WEAK int sys_bind(int socket, const struct sockaddr *address, socklen_t address_len) {
	return __set_errno(-ENOSYS);
}
