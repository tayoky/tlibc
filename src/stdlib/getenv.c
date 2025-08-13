#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern char **environ;

char *getenv(const char *name){
	//this is what we are searching
	char *search = malloc(strlen(name) + 2);
	if(!search){
		errno = ENOMEM;
		return NULL;
	}
	strcpy(search,name);
	strcat(search,"=");

	size_t name_len = strlen(search);

	//try to find the key
	int key = 0;
	while(environ[key]){
		//is it the good key ?
		if(strlen(environ[key]) >= name_len && !memcmp(environ[key],search,name_len)){
			break;
		}
		key++;
	}

	if(!environ[key]){
		//key not found
		errno = ESRCH;
		return NULL;
	}

	free(search);
	return environ[key] + name_len;
}
