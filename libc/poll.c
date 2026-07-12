#include <poll.h>
#include <sysdeps.h>

int poll(struct pollfd *fds, nfds_t nfds, int timeout) {
	return CALL_SYSDEP(sys_poll, (fds, nfds, timeout));
}
