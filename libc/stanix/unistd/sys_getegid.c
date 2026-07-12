#include <errno.h>
#include <syscall.h>
#include <unistd.h>

gid_t getegid(void) {
	return __set_errno(__syscall0(SYS_getegid));
}
