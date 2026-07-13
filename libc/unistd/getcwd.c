#include <unistd.h>
#include <sysdeps.h>

char *getcwd(char *buf, size_t size) {
	if (CALL_SYSDEP(sys_getcwd, (buf, size)) < 0) {
		return NULL;
	} else {
		return buf;
	}
}
