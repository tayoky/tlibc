#include <sysdeps.h>
#include <syscall.h>
#include <errno.h>

int sys_getgroups(int size, gid_t *list) {
	return __set_errno(__syscall2(SYS_getgroups, size, (long)list));
}
