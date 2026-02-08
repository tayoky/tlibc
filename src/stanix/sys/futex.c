#include <sys/futex.h>
#include <syscall.h>
#include <errno.h>

int futex(long *addr, int op, long val) {
	return __set_errno(__syscall3(SYS_futex, (long)addr, op, val));
}
