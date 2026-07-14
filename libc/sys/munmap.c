#include <sys/mman.h>
#include <sysdeps.h>

int munmap(void *addr, size_t length) {
	return sys_munmap(addr, length);
}
