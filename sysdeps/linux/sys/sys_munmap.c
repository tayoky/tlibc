#include <sysdeps.h>
#include <sys/syscall.h>
#include <unistd.h>

int sys_munmap(void *addr, size_t length) {
	return syscall(SYS_munmap, addr, length);
}
