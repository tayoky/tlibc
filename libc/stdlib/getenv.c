#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern char **environ;

char *getenv(const char *name) {
	size_t name_len = strlen(name);

	// try to find the key
	int key = 0;
	while (environ[key]) {
		// is it the good key ?
		if (strlen(environ[key]) >= name_len && !memcmp(environ[key], name, name_len) && environ[key][name_len] == '=') {
			break;
		}
		key++;
	}

	if (!environ[key]) {
		//key not found
		errno = ESRCH;
		return NULL;
	}

	return environ[key] + name_len + 1;
}
