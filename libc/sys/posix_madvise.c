#include <sys/mman.h>
#include <errno.h>

int posix_madvise(void *addr, size_t size, int advice) {
	int ret = madvise(addr, size, advice);
	return ret < 0 ? errno : ret;
}
