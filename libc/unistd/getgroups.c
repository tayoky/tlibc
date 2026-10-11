#include <unistd.h>
#include <sysdeps.h>

int getgroups(int size, gid_t *list) {
	return sys_getgroups(size, list);
}
