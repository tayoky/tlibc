#include <sysdeps.h>

TLIBC_WEAK int sys_setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len) {
	return SYSDEP_STUB;
}
