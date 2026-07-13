#include <errno.h>
#include <sysdeps.h>
#include <syscall.h>

int sys_poll(struct pollfd *fds, nfds_t nfds, int timeout) {
	return __set_errno(__syscall3(SYS_poll, (long)fds, (long)nfds, (long)timeout));
}
