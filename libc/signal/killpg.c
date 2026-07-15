#include <signal.h>
#include <errno.h>

int killpg(pid_t pgrp, int sig) {
	if (pgrp < 0) return __set_errno(-ESRCH);
	return kill(-pgrp, sig);
}
