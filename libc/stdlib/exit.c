#include <stdlib.h>
#include <tlibcnoreturn.h>
#include <unistd.h>

int __cxa_atexit(void (*func)(void *), void *arg, void *d);
void __cxa_finalize(void *d);

int atexit(void (*func)(void)){
	return __cxa_atexit((void*)func, NULL, NULL); 
}

TLIBC_NORETURN void exit(int status) {
	__cxa_finalize(NULL);
	_exit(status);
}
