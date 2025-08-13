#include <stdio.h>


int fflush(FILE *stream){
	if(stream == NULL){
		//TODO : fflush all streams
		return 0;
	}
	//TODO : fflush here when we add buffering
	stream->unget = EOF;
	return 0;
}
