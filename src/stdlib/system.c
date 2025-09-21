#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int system(const char *command){
	char *shell = getenv("SHELL");
	if(!shell){
		shell = "/bin/sh";
	}
	if(command == NULL){
		//check if a shell is availible
		return system("echo test") == 0;
	} else {
		pid_t child = fork();
		if(!child){
			char *argv[] = {
				shell,
				"-c",
				(char *)command,
				NULL
			};
			execvp(shell,argv);
			exit(127);
		}
		if(child < 0){
			return -1;
		}
		int status = 0;
		waitpid(child,&status,0);
		return status;
	}
}
