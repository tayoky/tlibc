#include <sys/resource.h>
#include <sysdeps.h>

int setrlimit(int resource, const struct rlimit *rlp) {
	return sys_setrlimit(resource, rlp);
}
