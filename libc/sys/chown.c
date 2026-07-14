#include <sys/stat.h>
#include <sysdeps.h>

int chown(const char *pathname, uid_t owner, gid_t group) {
	return sys_chown(pathname, owner, group);
}
