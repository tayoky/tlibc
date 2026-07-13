#include <sys/socket.h>
#include <sysdeps.h>
#include <errno.h>
#include <syscall.h>

int sys_shutdown(int socket, int how) {
	return __set_errno(__syscall2(SYS_shutdown, socket, how));
}
