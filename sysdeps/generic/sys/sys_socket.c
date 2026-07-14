#include <sysdeps.h>

TLIBC_WEAK int sys_socket(int domain, int type, int protocol) {
	return __set_errno(-ENOSYS);
}
