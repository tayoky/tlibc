#include <tlibc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void _init(void);
void _fini(void);

typedef void (*func)(void);

extern func _init_array_start[] __attribute__((weak));
extern func _fini_array_start[] __attribute__((weak));
extern func _init_array_end[] __attribute__((weak));
extern func _fini_array_end[] __attribute__((weak));

void __fini_tlibc(void){
	_fini();
	for (size_t i = 0; i < (_fini_array_end - _fini_array_start); i++){
		_fini_array_start[i]();
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
	for (size_t i = 0; i < (_init_array_end - _init_array_start); i++){
		_init_array_start[i]();
	}
	
}
