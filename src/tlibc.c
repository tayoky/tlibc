#include <tlibc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void _init(void);
void _fini(void);
int main(int argc,char **argv);

typedef void (*func)(void);

extern func __init_array_start[] __attribute__((weak));
extern func __fini_array_start[] __attribute__((weak));
extern func __init_array_end[] __attribute__((weak));
extern func __fini_array_end[] __attribute__((weak));

void __fini_tlibc(void){
	_fini();
	for (ptrdiff_t i = 0; i < (__fini_array_end - __fini_array_start); i++){
		__fini_array_start[i]();
	}
	fflush(NULL);
}

void __init_tlibc(int argc,char **argv,int envc,char **envp){
	(void)argc;
	(void)argv;
	__init_heap();
	__init_environ(envc,envp);

	atexit(__fini_tlibc);

	setlocale(LC_ALL,"POSIX");

	_init();
	for (ptrdiff_t i = 0; i < (__init_array_end - __init_array_start); i++){
		__init_array_start[i]();
	}
	exit(main(argc,argv));
}
