#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int remove(const char *pathname){
	int ret = unlink(pathname);

	//if it is a dir, use rmdir
	if(ret && errno == EISDIR){
		ret = rmdir(pathname);
	}

	return ret;
}
