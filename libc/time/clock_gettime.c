#include <time.h>
#include <sysdeps.h>

int clock_gettime(clockid_t clockid, struct timespec *tp) {
	return CALL_SYSDEP(sys_clock_gettime, (clockid, tp));
}
