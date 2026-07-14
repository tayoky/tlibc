#include <sysdeps.h>

TLIBC_WEAK int sys_set_tls(void *tls) {
	return __set_errno(-ENOSYS);
}
