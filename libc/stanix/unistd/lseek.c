#include <unistd.h>
#include <syscall.h>
#include <errno.h>

off_t lseek(int fd, off_t offset, int whence){
	return __set_errno(__syscall3(SYS_seek,fd,(long)offset,whence));
}
