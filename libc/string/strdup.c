#include <string.h>
#include <stdlib.h>

char *strdup(const char *str){
	char *newstr = malloc(strlen(str) + 1);
	return strcpy(newstr,str);
}
