#include <string.h>
#include <stdlib.h>

char *strndup(const char *str,size_t count){
	size_t len = strnlen(str,count);
	char *newstr = malloc(len + 1);
	newstr[len] = '\0';
	return memcpy(newstr,str,len);
}
