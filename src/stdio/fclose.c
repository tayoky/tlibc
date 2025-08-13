#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int fclose(FILE *stream){
	if(!stream)return __set_errno(-EBADF);
	if(close(stream->fd) < 0)return -1;
	free(stream);
	return 0;
}
