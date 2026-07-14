#include <sysdeps.h>

TLIBC_WEAK int sys_getsockopt(int socket, int level, int option_name, void *option_value, socklen_t *option_len) {
	return SYSDEP_STUB;
}
