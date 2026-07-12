#include <errno.h>
#include <sysdeps.h>
#include <tlibc.h>

int *__errno_location(void) {
#ifdef __LIBK__
	static int stub;
	return &stub;
#else
	// check if we have tls support
	if (!sys_set_tls) {
		static int err;
		return &err;
	}
	return &__get_uthread()->err;
#endif
}
