#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <stdio.h>
//environement variable manipulation
char **__environ;

void __init_environ(int argc,char **argv,int envc,char **envp){
	//envp is created by the kernel
	//so we can't realloc it
	//copy it to normal memory

	__environ = malloc((envc + 1) * sizeof(char *));
	for (size_t i = 0; i < envc; i++){
		__environ[i] = envp[i];
	}
	//last NULL entry
	__environ[envc] = NULL;
}

int putenv(char *str){
	if(!strchr(str,'=')){
		return __set_errno(-EINVAL);
	}

	//find name lenght
	size_t name_len = (uintptr_t)strchr(str,'=') - (uintptr_t)str + 1;

	//try to find the key
	int key = 0;
	while(__environ[key]){
		//is it the good key ?
		if(strlen(__environ[key]) > name_len && memcmp(__environ[key],str,name_len)){
			break;
		}
		key++;
	}
	
	if(!__environ[key]){
		//no key found
		__environ = realloc(__environ,(key + 2) * sizeof(char *));

		//set last NULL entry
		__environ[key + 1] = NULL;

		__environ[key] = str;
		return 0;
	}

	__environ[key] = str;
	return 0;
}

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

	printf("still here");

	//try to find the key
	int key = 0;
	while(__environ[key]){
		//is it the good key ?
		if(strlen(__environ[key]) > name_len && memcmp(__environ[key],search,name_len)){
			break;
		}
		key++;
	}

	if(!__environ[key]){
		//key not found
		return NULL;
	}

	free(search);
	printf("env find !!\n");
	return __environ[key] + name_len;
}