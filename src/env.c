#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include <tlibc.h>

//environement variable manipulation
char **environ;

void __init_environ(int envc,char **envp){
	//envp is created by the kernel
	//so we can't realloc it
	//copy it to normal memory

	environ = malloc((envc + 1) * sizeof(char *));
	for (size_t i = 0; i < envc; i++){
		environ[i] = envp[i];
	}
	//last NULL entry
	environ[envc] = NULL;
}

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