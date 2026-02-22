#include <stdio.h>
#include <limits.h>

char *gets(char *buffer){
	return fgets(buffer,INT_MAX,stdin);
}
