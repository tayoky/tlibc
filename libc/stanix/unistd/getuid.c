#include <errno.h>
#include <syscall.h>
#include <unistd.h>

uid_t getuid(void) {
	return __set_errno(__syscall0(SYS_getuid));
}
