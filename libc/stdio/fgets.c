#include <stdio.h>

char *fgets(char *string, int n, FILE *stream) {
	flockfile(stream);
	// read until '\n'
	int c = 0;
	char *ret = string;
	do {
		if (n <= 1) {
			break;
		}
		c = fgetc(stream);

		// if EOF quit immediatlely
		if (c == EOF) {
			if (ret == string) {
				funlockfile(stream);
				return NULL;
			}
			break;
		}

		*string = (char)c;
		string++;
		n--;
	} while (c != '\n');

	if (n >= 1) *string = '\0';
	funlockfile(stream);
	return ret;
}
