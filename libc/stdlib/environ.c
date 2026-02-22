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
	for (int i = 0; i < envc; i++){
		environ[i] = envp[i];
	}
	//last NULL entry
	environ[envc] = NULL;
}
