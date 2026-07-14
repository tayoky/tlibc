#include <sys/mman.h>
#include <sysdeps.h>

int mprotect(void *addr, size_t size, int prot) {
	return sys_mprotect(addr, size, prot);
}
