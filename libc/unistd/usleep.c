#include <time.h>
#include <sysdeps.h>
#include <unistd.h>

int usleep(useconds_t usec) {
	return sys_usleep(usec);
}
