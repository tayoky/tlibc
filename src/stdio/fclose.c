#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

extern FILE *__streams;

int fclose(FILE *stream){
	if(!stream)return __set_errno(-EBADF);
	//silently ignore attemp to close std stream
	if(stream == stdin || stream == stdout || stream == stderr)return 0;
	
	fflush(stream);
	if(close(stream->fd) < 0)return -1;
	if(stream->internalbuf) free(stream->buf);

	//remove from list of stream
	if(__streams == stream) __streams = stream->next;
	if(stream->next) stream->next->prev = stream->prev;
	if(stream->prev) stream->prev->next = stream->next;

	free(stream);
	return 0;
}
