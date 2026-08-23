#include <sysdeps.h>
#include <unistd.h>

void sync(void) {
	return sys_sync();
}
