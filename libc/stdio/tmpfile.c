#include <unistd.h>
#include <stdio.h>
#include <limits.h>

FILE *tmpfile(void){
	static long i = 0;
	char path[PATH_MAX];
	snprintf(path,PATH_MAX,"/tmp/tmp-%s.%s",getpid(),i++);
	//TODO : should we use open to be sure it's created ?
	//TODO : add mutex on multithreading
	FILE *file = fopen(path,"w+");
	if(file)unlink(path);
	return file;
}
