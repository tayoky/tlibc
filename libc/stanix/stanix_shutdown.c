#include <sys/shutdown.h>
#include <errno.h>
#include <syscall.h>

int stanix_shutdown(int flags) {
	return __set_errno(__syscall1(SYS_sys_shutdown, flags));
}
