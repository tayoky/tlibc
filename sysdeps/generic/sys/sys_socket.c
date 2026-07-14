#include <sysdeps.h>

TLIBC_WEAK int sys_socket(int domain, int type, int protocol) {
	return SYSDEP_STUB;
}
