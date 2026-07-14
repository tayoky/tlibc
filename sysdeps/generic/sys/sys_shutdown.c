#include <sysdeps.h>

TLIBC_WEAK int sys_shutdown(int socket, int how) {
	return __set_errno(-ENOSYS);
}
