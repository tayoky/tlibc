#include <sys/mman.h>
#include <syscall.h>
#include <errno.h>

int munmap(void *addr,size_t length){
	return __set_errno(__syscall2(SYS_munmap,(long)addr,length));
}
