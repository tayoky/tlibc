#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <tlibc.h>

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

	char *str;
	int ret = asprintf(&str, "%s=%s", name, value);
	if (ret < 0) return ret;

	if (environ[key]) {
		if (overwrite) {
			environ[key] = str;
		}
	} else  {
		// no key found
		ret = __grow_environ(str);
		if (ret < 0) {
			free(str);
			return ret;
		}
	}
	return 0;
}
