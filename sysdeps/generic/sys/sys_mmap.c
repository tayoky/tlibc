#include <sysdeps.h>
#include <sys/mman.h>

TLIBC_WEAK void *sys_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
	__set_errno(-ENOSYS);
	return MAP_FAILED;
}
