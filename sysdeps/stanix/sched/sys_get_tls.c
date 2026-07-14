#include <sysdeps.h>

void *sys_get_tls(void) {
	return sys_arch_get_tls();
}
