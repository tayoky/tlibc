#include <stdio.h>
#include <stdlib.h>

void __assert(const char *expr,const char *file,long line,const char *func){
	fprintf(stderr,"Assertion failed : %s, %s, %ld, function %s\n",expr,file,line,func);
	abort();
}