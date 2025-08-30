#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *__streams;

FILE *__create_stream(void){
	FILE *f = malloc(sizeof(FILE));
	if(!f)return NULL;
	memset(f,0,sizeof(FILE));
	f->unget = EOF;

	//link in the list
	if(__streams){
		__streams->prev = f;
	}
	f->next = __streams;
	__streams = f;
	return f;
}
