#include <sys/resource.h>
#include <sysdeps.h>

int getrlimit(int resource, struct rlimit *rlp) {
	return sys_getrlimit(resource, rlp);
}
