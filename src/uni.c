#include <sys/types.h>
#include <unistd.h>


pid_t getpgrp(void){
	return getpgid(getpid());
}

int setpgrp(void){
		return setpgid(0,0);
}