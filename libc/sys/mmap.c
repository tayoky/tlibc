#include <sys/mman.h>
#include <sysdeps.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
	if (sys_mmap) {
		return sys_mmap(addr, length, prot, flags, fd, offset);
	} else {
		__set_errno(-ENOSYS);
		return MAP_FAILED;
	}
}
