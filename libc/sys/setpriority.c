#include <sys/resource.h>
#include <sysdeps.h>

int setpriority(int which, id_t who, int value) {
	return sys_setpriority(which, who, value);
}
