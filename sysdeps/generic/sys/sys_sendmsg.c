#include <sysdeps.h>

TLIBC_WEAK ssize_t sys_sendmsg(int socket, const struct msghdr *message, int flags) {
	return __set_errno(-ENOSYS);
}
