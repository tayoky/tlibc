#include <poll.h>
#include <syscall.h>
#include <errno.h>

int poll(struct pollfd *fds, nfds_t nfds, int timeout){
	return __set_errno(__syscall3(SYS_poll,(long)fds,(long)nfds,(long)timeout));
}
