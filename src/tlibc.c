#include <tlibc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void __fini_tlibc(void){
	fflush(NULL);
}

void __init_tlibc(int argc,char **argv,int envc,char **envp){
	(void)argc;
	(void)argv;
	__init_heap();
	__init_environ(envc,envp);

	atexit(__fini_tlibc);
}
