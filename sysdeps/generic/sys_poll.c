#include <sysdeps.h>

TLIBC_WEAK int sys_poll(struct pollfd *fds, nfds_t nfds, int timeout) {
	return SYSDEP_STUB;
}
