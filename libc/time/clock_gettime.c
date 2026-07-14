#include <time.h>
#include <sysdeps.h>

int clock_gettime(clockid_t clockid, struct timespec *tp) {
	return sys_clock_gettime(clockid, tp);
}
