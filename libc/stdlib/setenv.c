#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

extern char **environ;

int setenv(const char *name, const char *value, int overwrite) {
	if (!name || strchr(name, '=')) return __set_errno(-EINVAL);
	if (!value) return __set_errno(-EINVAL);

	// try to find the key
	int key = 0;
	size_t name_len = strlen(name);
	while (environ[key]) {
		// is it the good key ?
		if (strncmp(environ[key], name, name_len) == 0 && environ[key][name_len] == '=') {
			break;
		}
		key++;
	}

	if (environ[key]) {
		if (!overwrite) return 0;
	} else  {
		// no key found
		environ = realloc(environ, (key + 2) * sizeof(char *));

		// set last NULL entry
		environ[key + 1] = NULL;
	}

	return asprintf(&environ[key], "%s=%s", name, value);
}
