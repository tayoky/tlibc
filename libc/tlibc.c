#include <tlibc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <locale.h>

#ifndef __DYNAMIC__
void _init(void);
void _fini(void);
#endif

typedef void (*func)(void);

extern func __init_array_start[] __attribute__((weak));
extern func __fini_array_start[] __attribute__((weak));
extern func __init_array_end[] __attribute__((weak));
extern func __fini_array_end[] __attribute__((weak));

#ifndef __DL_TLIBC__
static void __fini_tlibc(void) {
#ifndef __DYNAMIC__ // dynamic linker aready call destructors
	_fini();
	for (ptrdiff_t i = 0; i < (__fini_array_end - __fini_array_start); i++) {
		__fini_array_start[i]();
	}
#endif
	fflush(NULL);
}
#endif

void __init_tlibc(int argc, char **argv, int envc, char **envp, main_t main) {
	(void)argc;
	(void)argv;
	(void)envc;

#ifndef __DYNAMIC__ // dynamic linker aready prepare uthread
	//setup a uthread for the main thread
	__set_tls(__new_uthread());
#endif
#ifndef __DL_TLIBC__
	__init_heap();
#endif

	// the dynamic linker need environ access
	__init_environ(envc, envp);

#ifndef __DL_TLIBC__
	atexit(__fini_tlibc);

#ifndef __DYNAMIC__ // dynamic linker aready call constructors
	_init();
	for (ptrdiff_t i = 0; i < (__init_array_end - __init_array_start); i++) {
		__init_array_start[i]();
	}
#endif
#endif
	exit(main(argc, argv, envp));
}
