#include <errno.h>
#include <sysdeps.h>
#include <tlibc.h>

int *__errno_location(void) {
#ifdef __LIBK__
	static int stub;
	return &stub;
#else
	static int err;
	struct __uthread *uthread = __get_uthread();
	return uthread ? &uthread->err : &err;
#endif
}
