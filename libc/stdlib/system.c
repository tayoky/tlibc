#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int system(const char *command) {
	if (command == NULL) {
		// check if a shell is availible
		return system("") == 0;
	} else {
		pid_t child = fork();
		if (!child) {
			execl("/bin/sh", "/bin/sh", "-c", (char *)command, NULL);
			_exit(127);
		}
		if (child < 0) {
			return -1;
		}
		int status = 0;
		waitpid(child, &status, 0);
		return status;
	}
}
