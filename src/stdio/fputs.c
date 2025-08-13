#include <stdio.h>
#include <string.h>

int fputs(const char *str,FILE *stream){
	stream->errno = 0;
	return !fwrite(str,sizeof(char),strlen(str),stream) && stream->errno ? -1 : 0;
}
