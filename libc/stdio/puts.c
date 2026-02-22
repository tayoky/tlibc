#include <stdio.h>

int puts(const char *str){
	if(fputs(str,stdout) < 0){
		return -1;
	}
	return putchar('\n') != EOF ? 0 : -1 ;
}
