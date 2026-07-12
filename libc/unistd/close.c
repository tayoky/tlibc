#include <unistd.h>
#include <sysdeps.h>

int close(int fd) {
	return CALL_SYSDEP(sys_close, (fd));
}
