#include <stdio.h>
#include <string.h>

int fputs(const char *str,FILE *stream){
	stream->error = 0;
	return !fwrite(str,sizeof(char),strlen(str),stream) && stream->error ? -1 : 0;
}
