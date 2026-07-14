#include <sysdeps.h>
#include <stddef.h>

TLIBC_WEAK int sys_usleep(useconds_t usec) {
	struct timespec ts = {
		.tv_sec = usec / 1000000,
		.tv_nsec = (usec / 1000) % 1000,
	};
	return sys_nanosleep(&ts, NULL);
}
