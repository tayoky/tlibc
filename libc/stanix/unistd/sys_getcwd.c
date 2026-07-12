#include <errno.h>
#include <syscall.h>
#include <unistd.h>

char *getcwd(char *buf, size_t size) {
	if (__set_errno(__syscall2(SYS_getcwd, (long)buf, (long)size))) {
		return NULL;
	} else {
		return buf;
	}
}
