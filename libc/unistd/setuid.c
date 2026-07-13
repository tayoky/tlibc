#include <unistd.h>
#include <sysdeps.h>

int setuid(uid_t uid) {
	return CALL_SYSDEP(sys_setuid, (uid));
}
