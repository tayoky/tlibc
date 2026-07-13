#include <time.h>
#include <sysdeps.h>
#include <unistd.h>

int usleep(useconds_t usec) {
	if (sys_usleep) {
		return sys_usleep(usec);
	} else if (sys_nanosleep) {
		struct timespec ts = {
			.tv_sec = usec / 1000000,
			.tv_nsec = (usec / 1000) % 1000,
		};
		return sys_nanosleep(&ts, NULL);
	} else {
		return __set_errno(-ENOSYS);
	}
}
