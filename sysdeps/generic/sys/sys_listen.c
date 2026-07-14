#include <sysdeps.h>

TLIBC_WEAK int sys_listen(int socket, int backlog) {
	return __set_errno(-ENOSYS);
}
