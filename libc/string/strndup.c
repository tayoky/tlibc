#include <stdlib.h>
#include <string.h>

char *strndup(const char *str, size_t count) {
	size_t len = strnlen(str, count);
	char *newstr = malloc(len + 1);
	if (!newstr) return NULL;
	newstr[len] = '\0';
	return memcpy(newstr, str, len);
}
