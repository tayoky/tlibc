#include <stdio.h>
#include <unistd.h>

extern FILE *__streams;

int fflush(FILE *stream){
	if(stream == NULL){
		fflush(stdout);
		fflush(stdin);
		fflush(stderr);
		stream = __streams;
		while(stream){
			fflush(stream);
			stream = stream->next;
		}
		return 0;
	}
	stream->unget = EOF;
	if(stream->buftype == _IONBF) return 0;
	ssize_t w = write(stream->fd,stream->buf,stream->usedsize);
	stream->usedsize = 0;
	return w < 0 ? -1 : 0;
}
