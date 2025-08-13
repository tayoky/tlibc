#include <stdio.h>

int fputc(int lc,FILE *stream){
	unsigned char c = (unsigned char)lc;
	return fwrite(&c,sizeof(c),1,stream) ? lc : EOF;
}
