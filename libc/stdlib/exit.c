#include <limits.h>
#include <stdlib.h>
#include <tlibcnoreturn.h>
#include <unistd.h>

static void (*atexit_funcs[ATEXIT_MAX])(void);
static int atexit_count = 0;

int atexit(void (*func)(void)){
	if(atexit_count >= 64){
		return -1;
	}
	atexit_funcs[atexit_count] = func;
	atexit_count++;
	return 0;
}


TLIBC_NORETURN void exit(int status) {
	for (int i = atexit_count - 1; i >= 0; i--) {
		atexit_funcs[i]();
	}
	_exit(status);
}
