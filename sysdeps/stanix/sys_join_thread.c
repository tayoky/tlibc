#include <sysdeps.h>

int sys_join_thread(pid_t tid, void **arg) {
	(void)tid;
	(void)arg;
	// Stanix does not have sys_join_thread anymore
	return 0;
}
