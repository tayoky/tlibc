#include <sys/mman.h>
#include <sysdeps.h>

int madvise(void *addr, size_t size, int advice) {
	return sys_madvise(addr, size, advice);
}
