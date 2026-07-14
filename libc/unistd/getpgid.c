#include <unistd.h>
#include <sysdeps.h>

pid_t getpgid(pid_t pid) {
	return sys_getpgid(pid);
}
