#include <time.h>
#include <sysdeps.h>

int nanosleep(const struct timespec *duration, struct timespec *rem) {
	// TODO : fallback using usleep
	return CALL_SYSDEP(sys_nanosleep, (duration, rem));
}
