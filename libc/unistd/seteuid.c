#include <unistd.h>
#include <sysdeps.h>

int seteuid(uid_t uid) {
	return CALL_SYSDEP(sys_seteuid, (uid));
}
