#include <sysdeps.h>

TLIBC_WEAK int sys_connect(int socket, const struct sockaddr *address, socklen_t address_len) {
	return SYSDEP_STUB;
}
