#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tlibc.h>
#include <unistd.h>

// environ growing
extern char **envirion;
static char **array = NULL;

int __grow_environ(const char *str) {
	int envc = 0;
	while (environ[envc]) envc++;

	if (array == environ) {
		// we can grow environ
		char **new = realloc(array, (envc + 2) * sizeof(char));
		if (!new) return -1;
		array = new;
	} else {
		// we need to copy the environ
		char **new = malloc((envc + 2) * sizeof(char *));
		if (!new) return -1;
		free(array);
		array = new;
		for (int i = 0; i < envc; i++) {
			array[i] = environ[i];
		}
	}
	array[envc] = (char*)str;
	array[envc + 1] = NULL;
	environ = array;
	return 0;
}
