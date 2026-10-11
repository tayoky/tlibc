#include <sysdeps.h>
#include <syscall.h>
#include <errno.h>

int sys_setgroups(size_t size, const gid_t *list) {
	return __set_errno(__syscall2(SYS_setgroups, size, (long)list));
}
