#include <errno.h>
#include <sched.h>
#include <syscall.h>

int stanix_set_tls(void *tls) {
	return __set_errno(__syscall1(SYS_settls, (long)tls));
}
