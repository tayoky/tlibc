#include <sysdeps.h>
#include <sys/resource.h>

TLIBC_WEAK int sys_getrlimit(int resource, struct rlimit *rlp) {
	(void)resource;
	rlp->rlim_cur = RLIM_INFINITY;
	rlp->rlim_max = RLIM_INFINITY;
	return SYSDEP_STUB;
}
