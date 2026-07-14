#include <unistd.h>
#include <sysdeps.h>

int seteuid(uid_t uid) {
	return sys_seteuid(uid);
}
