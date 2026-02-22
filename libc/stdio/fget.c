#include <stdio.h>

int fgetc(FILE *stream){
	unsigned char c = 0;
	return fread(&c,sizeof(c),1,stream) ? c : EOF;
}
