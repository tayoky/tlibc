#include <sys/stat.h>
#include <sysdeps.h>

int lchown(const char *pathname, uid_t owner, gid_t group) {
	return sys_lchown(pathname, owner, group);
}
