#include <unistd.h>
#include <sysdeps.h>

int setuid(uid_t uid) {
	return sys_setuid(uid);
}
