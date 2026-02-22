#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

extern char **environ;

int putenv(char *str){
	if(!strchr(str,'=')){
		return __set_errno(-EINVAL);
	}

	//find name lenght
	size_t name_len = (uintptr_t)strchr(str,'=') - (uintptr_t)str + 1;

	//try to find the key
	int key = 0;
	while(environ[key]){
		//is it the good key ?
		if(strlen(environ[key]) > name_len && !memcmp(environ[key],str,name_len)){
			break;
		}
		key++;
	}
	
	if(!environ[key]){
		//no key found
		environ = realloc(environ,(key + 2) * sizeof(char *));

		//set last NULL entry
		environ[key + 1] = NULL;

		environ[key] = str;
		return 0;
	}

	environ[key] = str;
	return 0;
}
