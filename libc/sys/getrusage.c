#include <sys/resource.h>
#include <sysdeps.h>

int getrusage(int who, struct rusage *r_usage) {
	return sys_getrusage(who, r_usage);
}
