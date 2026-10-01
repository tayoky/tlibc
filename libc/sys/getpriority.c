#include <sys/resource.h>
#include <sysdeps.h>

int getpriority(int which, id_t who) {
	return sys_getpriority(which, who);
}
