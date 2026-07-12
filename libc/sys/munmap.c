#include <sys/mman.h>
#include <sysdeps.h>

int munmap(void *addr, size_t length) {
	return CALL_SYSDEP(sys_munmap, (addr, length));
}
