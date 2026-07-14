#include <unistd.h>
#include <sysdeps.h>

char *getcwd(char *buf, size_t size) {
	if (sys_getcwd(buf, size) < 0) {
		return NULL;
	} else {
		return buf;
	}
}
