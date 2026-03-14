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

void __init_tlibc(long *stack, main_t main) {
	int argc = *stack;
	char **argv = (char **)(stack + 1);
	char **envp = (char **)(stack + argc + 2);

#ifndef __DYNAMIC__ // dynamic linker aready prepare uthread
	//setup a uthread for the main thread
	__set_tls(__new_uthread());
#endif
#ifdef __DL_TLIBC__
	// the dynamic linker cannot use static stdio
	// because it cannot have reloc
	__init_stdio();
#else
	__init_heap();
#endif

	// the dynamic linker need environ access
	__init_environ(envp);

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
