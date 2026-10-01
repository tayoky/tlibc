#include <sysdeps.h>
#include <sys/resource.h>
#include <string.h>

TLIBC_WEAK int sys_getrusage(int who, struct rusage *r_usage) {
	(void)who;
	memset(r_usage, 0, sizeof(struct rusage));
	return SYSDEP_STUB;
}
