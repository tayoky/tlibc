#include <stdio.h>

int ungetc(int c,FILE *stream){
	//TODO : move position indicator
	if(stream->unget != EOF || c == EOF){
		return EOF;
	}
	stream->eof = 0;
	stream->unget = c;
	return c;
}
