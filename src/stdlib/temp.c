#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

int mkostemp(char *template, int flags){
	if(strlen(template) < 6 || strcmp("XXXXXX",&template[strlen(template) - 6])){
		return __set_errno(-EINVAL);
	}

	int id = (int)getpid();

	char *suffix = &template[strlen(template) - 6];
	

	for (size_t i = 0; i < 128; i++){
		sprintf(suffix,"%d",id);
		int fd = open(template,O_CREAT | O_EXCL | O_RDWR | flags, S_IRUSR | S_IWUSR);
		if(fd >= 0){
			return fd;
		}
		
		if(errno != EEXIST){
			return -1;
		}

		id++;
	}

	return __set_errno(-EEXIST);
}

int mkstemp(char *template){
	return mkostemp(template,0);
}

char *mktemp(char *template){
	int fd = mkstemp(template);
	if(fd < 0){
		template[0] = '\0';
	} else {
		close(fd);
	}

	return template;
}