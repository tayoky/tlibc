#include <stdio.h>

int puts(const char *str) {
	flockfile(stdout);
	if (fputs(str, stdout) < 0) {
		funlockfile(stdout);
		return -1;
	}
	int ret = putchar_unlocked('\n') != EOF ? 0 : -1;
	funlockfile(stdout);
	return ret;
}
