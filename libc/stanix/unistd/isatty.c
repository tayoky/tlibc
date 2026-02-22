#include <unistd.h>
#include <syscall.h>
#include <errno.h>

int isatty(int fd){
	int ret = __syscall1(SYS_isatty,(long)fd);
	//isatty is a bit diferent at it should return 0 and not -1;
	if(ret < 0){
		errno = -ret;
		return 0;
	}

	return ret;
}
