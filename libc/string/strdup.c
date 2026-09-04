#include <stdlib.h>
#include <string.h>

char *strdup(const char *str) {
	char *newstr = malloc(strlen(str) + 1);
	if (!newstr) return NULL;
	return strcpy(newstr, str);
}
