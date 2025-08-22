#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern char **environ;
int unsetenv(const char *name){
	//this is what we are searching
	char *search = malloc(strlen(name) + 2);
	if(!search){
		errno = ENOMEM;
		return -1;
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
	free(search);

	if(!environ[key]){
		//key not found
		errno = ESRCH;
		return -1;
	}

	//replace with last
	int last = 0;
	while(environ[last]){
		last++;
	}
	last--;
	environ[key] = environ[last];

	//and replace last with null
	environ[last] = NULL;
	return 0;
}
