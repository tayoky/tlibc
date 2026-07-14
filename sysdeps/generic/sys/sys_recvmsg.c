#include <sysdeps.h>

TLIBC_WEAK ssize_t sys_recvmsg(int socket, struct msghdr *message, int flags) {
	return SYSDEP_STUB;
}
