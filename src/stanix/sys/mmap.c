#include <sys/mman.h>
#include <syscall.h>
#include <errno.h>

void *mmap(void *addr,size_t length,int prot,int flags,int fd,off_t offset){
	void *ret = (void *)__syscall6(SYS_mmap,(long)addr,length,prot,flags,fd,offset);
	if(ret >  (void *)0xFFFFF00000000000){
		errno = -(long)ret;
		return map_failed;
	}

	return ret;
}
