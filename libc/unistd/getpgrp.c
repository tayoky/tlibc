#include <unistd.h>

pid_t getpgrp(void) {
	return getpgid(getpid());
}
