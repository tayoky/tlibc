#include <time.h>
#include <sysdeps.h>

int clock_settime(clockid_t clock_id, const struct timespec *tp) {
	return sys_clock_settime(clock_id, tp);
}
