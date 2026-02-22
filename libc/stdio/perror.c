#include <stdio.h>
#include <errno.h>
#include <string.h>

void perror(const char *string){
	fprintf(stderr,"%s : %s\n",string,strerror(errno));
}
