#include <sys/stat.h>
#include <sysdeps.h>

int fchown(int fd, uid_t owner, gid_t group) {
	return sys_fchown(fd, owner, group);
}
