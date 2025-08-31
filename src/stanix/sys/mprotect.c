#include <sys/mman.h>
#include <syscall.h>
#include <errno.h>

int mprotect(void *addr,size_t size,int prot){
	return __set_errno(__syscall3(SYS_mprotect,(long)addr,size,prot));
}
